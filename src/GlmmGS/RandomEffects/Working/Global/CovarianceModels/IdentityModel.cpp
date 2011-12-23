#include "../../../../Standard.h"
#include "../../../../Estimate.h"
#include "IdentityModel.h"

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
					// Construction
					IdentityModel::IdentityModel(int nvars)
						: ICovarianceModel(1), size(nvars)
					{
						this->theta(0) = 1.0;
					}

					IdentityModel::~IdentityModel()
					{
					}

					// Properties
					Vector<double> IdentityModel::CoefficientsVariance() const
					{
						const TriangularMatrix<double> covariance = this->beta_precision_chol.Inverse();
						return LinearAlgebra::Diagonal(covariance);
					}

					// Methods
					void IdentityModel::Decompose(const TriangularMatrix<double> & design_precision)
					{
						// Add diagonal to precision
						TriangularMatrix<double> prec = design_precision;
						for (int i = 0; i < this->size; ++i)
							prec(i, i) += this->theta(0);

						// Decompose
						this->beta_precision_chol.Decompose(prec);
					}

					int IdentityModel::Update(const Vector<double> & beta, Comparer comparer)
					{
						// Calculate variance
						const TriangularMatrix<double> covariance = this->beta_precision_chol.Inverse();

						// Calculate jacobian and minus the hessian
						Vector<double> jac(1);
						TriangularMatrix<double> minus_hessian(1);
						const double bsquare = LinearAlgebra::Square(beta);
						const double trace = LinearAlgebra::Trace(covariance);
						jac(0) = this->size / this->theta(0) - bsquare - trace;
						minus_hessian(0, 0) = this->size / Math::Square(this->theta(0)) - LinearAlgebra::SquareTrace(covariance);

						// Update covariance components
						return ICovarianceModel::Update(minus_hessian, jac, comparer);
					}

					Vector<double> IdentityModel::CoefficientsUpdate(const Vector<double> & jacobian, const Vector<double> & beta) const
					{
						// Add diagonal terms
						Vector<double> jac = jacobian;
						for (int i = 0; i < this->size; ++i)
							jac(i) -= this->theta(0) * beta(i);

						// Decomposes
						return this->beta_precision_chol.Solve(jac);
					}
				}
			}
		}
	}
}
