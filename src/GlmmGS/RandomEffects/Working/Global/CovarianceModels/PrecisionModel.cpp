#include "../../../../Standard.h"
#include "../../../../Estimate.h"
#include "PrecisionModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Global
			{
				namespace CovarianceModels
				{
					// Helpers

					// Weighted square norm of vector
					double Square(WeakMatrix<const double> m, const Vector<double> & x)
					{
						_ASSERT_ARGUMENT(m.NumberOfRows() == x.Size() && m.NumberOfColumns() == x.Size());
						const int size = x.Size();
						double sum = 0.0;
						for (int i = 0; i < size; ++i)
						{
							sum += m(i, i) * Math::Square(x(i));
							for (int j = 0; j < i; ++j)
								sum += 2.0 * m(i, j) * x(i) * x(j);
						}
						return sum;
					}

					// Trace
					double Trace(const Matrix<double> & a)
					{
						const int size = a.NumberOfColumns();
						double sum = 0.0;
						for (int i = 0; i < size; ++i)
							sum += a(i, i);
						return sum;
					}

					// Trace of square product
					double SquareTrace(const Matrix<double> & a)
					{
						const int size = a.NumberOfColumns();
						double sum = 0.0;
						for (int i = 0; i < size; ++i)
							for (int j = 0; j < size; ++j)
								sum += a(i, j) * a(j, i);
						return sum;
					}

					// Matrix-vector product
					double MatrixProduct(int k, WeakMatrix<const double> m, const Vector<double> & x)
					{
						const int size = m.NumberOfRows();
						double sum = 0.0;
						for (int i = 0; i < size; ++i)
							sum += m(k, i) * x(i);
						return sum;
					}

					// Construction
					PrecisionModel::PrecisionModel(WeakMatrix<const double> R)
						: ICovarianceModel(1), R(R)
					{
						this->theta = 1.0;
					}

					PrecisionModel::~PrecisionModel()
					{
					}

					// Properties
					Vector<double> PrecisionModel::CoefficientsVariance() const
					{
						const TriangularMatrix<double> covariance = this->beta_precision_chol.Inverse();
						return LinearAlgebra::Diagonal(covariance);
					}

					// Methods
					void PrecisionModel::Decompose(const TriangularMatrix<double> & design_precision)
					{
						// Add diagonal to precision
						TriangularMatrix<double> prec = design_precision;
						const int size = this->R.NumberOfRows();
						for (int i = 0; i < size; ++i)
						{
							prec(i, i) += this->theta(0) * this->R(i, i);
							for (int j = 0; j < i; ++j)
								prec(i, j) += this->R(i, j);
						}

						// Decompose
						this->beta_precision_chol.Decompose(prec);
					}

					int PrecisionModel::Update(const Vector<double> & beta, Comparer comparer)
					{
						// Calulate T^{-1} R
						const int ncols = this->R.NumberOfColumns();
						Matrix<double> a(ncols, ncols);
						Vector<double> b(ncols);
						for (int j = 0; j < ncols; ++j)
						{
							// Prepare b
							for (int i = 0; i < ncols; ++i)
								b(i) = this->R(i, j);

							// Solve T x = b
							Vector<double> x = this->beta_precision_chol.Solve(b);

							// Store x
							for (int i = 0; i < ncols; ++i)
								a(i, j) = x(i);
						}

						// Calculate jacobian and minus the hessian
						Vector<double> jac(1);
						TriangularMatrix<double> minus_hessian(1);
						const double bsquare = Square(this->R, beta);
						const double trace = Trace(a);
						jac(0) = ncols / this->theta(0) - bsquare - trace;
						minus_hessian(0, 0) = ncols / Math::Square(this->theta(0)) - SquareTrace(a);

						// Update covariance components
						return ICovarianceModel::Update(minus_hessian, jac, comparer);
					}

					Vector<double> PrecisionModel::CoefficientsUpdate(const Vector<double> & design_jacobian, const Vector<double> & beta) const
					{
						// Add diagonal terms
						const int size = this->R.NumberOfRows();
						Vector<double> jac(size);
						for (int i = 0; i < size; ++i)
							jac(i) = design_jacobian(i) - this->theta(0) * MatrixProduct(i, this->R, beta);

						// Solve
						return this->beta_precision_chol.Solve(jac);
					}
				}
			}
		}
	}
}
