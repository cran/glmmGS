#include "../../../../Standard.h"
#include "../../../../Estimate.h"
#include "SparsePrecisionModel.h"
#include "Functions.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				namespace CovarianceModels
				{
					// Construction
					SparsePrecisionModel::SparsePrecisionModel(int nvars, const LDL::SparseMatrix<double> & R)
						: ICovarianceModel(nvars), nvars(nvars), R(R)
					{
						this->theta = 1.0;
					}

					SparsePrecisionModel::~SparsePrecisionModel()
					{
					}

					// Properties
					Vector<double> SparsePrecisionModel::CoefficientsVariance() const
					{
						// Calculate standard-errors
						const int nlevels = this->R.NumberOfColumns();
						const int size = this->nvars * nlevels;
						Vector<double> variance(size);
						NewTypes::Vector<double> b(size);
						for (int j = 0, jk = 0; j < this->nvars; ++j)
						{
							for (int k = 0; k < nlevels; ++k, ++jk)
							{
								// Prepare b
								NewTypes::Set(b, 0.0);
								b(jk) = 1.0;

								// Solve T_j x = b
								NewTypes::Vector<double> x = this->beta_precision_chol.Solve(b);

								// Calculate standard-error
								variance(jk) = x(jk);
							}
						}
						return variance;
					}

					// Methods
					void SparsePrecisionModel::Decompose(const TriangularMatrix<Vector<double> > & design_precision)
					{
						// Build an upper diagonal sparse-matrix equal to the design-precision plus the random-effects-precision

						// Number of levels of the stratified random effect
						const int nlevels = this->R.NumberOfColumns();

						// Number of non-zero entries of the sparse matrix
						const int count = this->R.Count(nlevels) * this->nvars + nlevels * (this->nvars * (this->nvars - 1));
						const int ncols = nlevels * this->nvars;

						// Data structures of the sparse matrix
						NewTypes::Vector<double> values(count);
						NewTypes::Vector<int> indices(count);
						NewTypes::Vector<int> counts(ncols + 1);

						// Set vector of counts
						counts(0) = 0;
						for (int index = 0, i = 0; i < this->nvars; ++i)
						{
							for (int k = 0; k < nlevels; ++k, ++index)
							{
								const int nelements = (this->nvars - 1) + (this->R.Count(k + 1) - this->R.Count(k));
								counts(index + 1) = counts(index) + nelements;
							}
						}

						// Set values and indices
						for (int index = 0, i = 0; i < this->nvars; ++i)
						{
							const double tau_i = this->theta(i);
							const Vector<double> & design_precision_i = design_precision(i, i);
							const int offset_i = i * nlevels;

							for (int k = 0; k < nlevels; ++k)
							{
								// Upper-diagonal blocks
								for (int j = 0; j < i; ++j)
								{
									values(index) = design_precision(i, j)(k);
									indices(index) = j * nlevels + k;
									++index;
								}

								// Diagonal block
								const int p2 = this->R.Count(k + 1);
								for (int p = this->R.Count(k); p < p2; ++p)
								{
									const int l = this->R.Index(p);
									if (l != k)
									{
										// Off-diagonal elements
										values(index) = tau_i * this->R.Value(p);
										indices(index) = offset_i + l;
										++index;
									}
									else
									{
										// Diagonal elements
										values(index) = design_precision_i(k) + tau_i * this->R.Value(p);
										indices(index) = offset_i + l;
										++index;
									}
								}

								// Lower-diagonal blocks
								for (int j = i + 1; j < this->nvars; ++j)
								{
									values(index) = design_precision(j, i)(k);
									indices(index) = j * nlevels + k;
									++index;
								}
							}
						}

						// Build sparse precision matrix
						LDL::SparseMatrix<double> upper(values, indices, counts);

						// Decompose sparse precision matrix
						this->beta_precision_chol.Decompose(upper);
					}

					int SparsePrecisionModel::Update(const Vector<Vector<double> > & beta, Comparer comparer)
					{
						// Calulate T^{-1} R
						const int nlevels = this->R.NumberOfColumns();
						const int size = this->nvars * nlevels;
						Matrix<double> a(size, size);
						NewTypes::Vector<double> b(size);
						for (int j = 0, jk = 0; j < this->nvars; ++j)
						{
							const int offset = j * nlevels;
							for (int k = 0; k < nlevels; ++k, ++jk)
							{
								// Prepare b
								NewTypes::Set(b, 0.0);
								const int p2 = this->R.Count(k + 1);
								for (int p = this->R.Count(k); p < p2; ++p)
								{
									const int i = this->R.Index(p);
									b(offset + i) = this->R.Value(p);
								}

								// Solve T_j x = b
								NewTypes::Vector<double> x = this->beta_precision_chol.Solve(b);

								// Store x
								for (int i = 0; i < size; ++i)
									a(i, jk) = x(i);
							}
						}

						// Calculate jacobian and minus the hessian
						Vector<double> jac(this->nvars);
						TriangularMatrix<double> minus_hessian(this->nvars);
						for (int i = 0; i < this->nvars; ++i)
						{
							const double bsquare = Square(this->R, beta(i));
							jac(i) = nlevels / this->theta(i) - bsquare - BlockTrace(i, nlevels, a);
							minus_hessian(i, i) = nlevels / Math::Square(this->theta(i)) - BlockSquareTrace(i, i, nlevels, a);
							for (int j = 0; j < i; ++j)
								minus_hessian(i, j) = -BlockSquareTrace(i, j, nlevels, a);
						}

						// Update covariance components
						return ICovarianceModel::Update(minus_hessian, jac, comparer);
					}

					Vector<Vector<double> > SparsePrecisionModel::CoefficientsUpdate(const Vector<Vector<double> > & design_jacobian, const Vector<Vector<double> > & beta) const
					{
						// Add diagonal terms
						const int nlevels = this->R.NumberOfColumns();
						NewTypes::Vector<double> jac(nlevels * this->nvars);
						for (int index = 0, i = 0; i < this->nvars; ++i)
							for (int k = 0; k < nlevels; ++k, ++index)
							{
								// Notice that since R = R^T, we can use a transpose matrix product
								// optimized by the column-sparse structure of R
								jac(index) = design_jacobian(i)(k) - this->theta(i) * TMatrixProduct(k, this->R, beta(i));
							}

						// Solve
						NewTypes::Vector<double> h_tmp = this->beta_precision_chol.Solve(jac);

						// Copy update. TODO: Change return type to NewType::Vector
						Vector<Vector<double> > h(this->nvars);
						for (int index = 0, i = 0; i < this->nvars; ++i)
						{
							h(i).Size(nlevels);
							for (int k = 0; k < nlevels; ++k, ++index)
								h(i)(k) = h_tmp(index);
						}

						return h;
					}
				}
			}
		}
	}
}
