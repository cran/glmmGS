#include "../../../Standard.h"
#include "../../../Estimate.h"
#include "../../../Variables/IVariable.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "Block.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Global
			{
				// Block
				Block::Block(Vector<Pointer<Variables::IVariable> > variables, Pointer<CovarianceModels::ICovarianceModel> covariance_model)
					: variables(variables), beta(variables.Size()), covariance_model(covariance_model)
				{
				}

				Vector<Estimate> Block::Coefficients() const
				{
					Vector<Estimate> estimates(this->beta.Size());
					Vector<double> variance = this->covariance_model->CoefficientsVariance();
					for (int i = 0; i < this->beta.Size(); ++i)
						estimates(i) = Estimate(this->beta.Value(i), variance(i));
					return estimates;
				}

				Vector<Estimate> Block::CovarianceComponents() const
				{
					return this->covariance_model->Estimates();
				}

				void Block::UpdatePredictor(Vector<double> & eta) const
				{
					const int nvars = this->variables.Size();
					for (int j = 0; j < nvars; ++j)
						this->variables(j)->UpdatePredictor(eta, this->beta.Value(j));
				}

				int Block::Update(const Vector<double> & weights, const Vector<double> & values, Comparer comparer)
				{
					const int nvars = this->variables.Size();
					Vector<double> jacobian(nvars);
					TriangularMatrix<double> precision(nvars);
					for (int j = 0; j < nvars; ++j)
					{
						// Evaluate jacobian
						jacobian(j) = Variables::ScalarProduct(this->variables(j), values);
						// Evaluate precision
						for (int k = 0; k <= j; ++k)
							precision(j, k) = Variables::ScalarProduct(this->variables(j), weights, this->variables(k));
					}

					// Calculate update
					this->covariance_model->Decompose(precision);
					int update = 0;
					update += this->beta.Update(jacobian, this->covariance_model, comparer);
					update += this->covariance_model->Update(this->beta.Values(), comparer);
					return update;
				}
			}
		}
	}
}
