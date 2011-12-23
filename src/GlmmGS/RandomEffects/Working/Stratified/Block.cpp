#include "../../../Standard.h"
#include "../../../Variables/IVariable.h"
#include "../../../Estimate.h"
#include "Block.h"
#include "Boosters/IBooster.h"
#include "CovarianceModels/ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				// Block
				Block::Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Pointer<Boosters::IBooster> booster)
					: variables(variables),
					  factor(factor),
					  beta(variables.Size(), factor.NumberOfLevels(), booster),
					  covariance_model(covariance_model)
				{
				}

				Vector<Estimate> Block::Coefficients() const
				{
					Vector<Estimate> estimates(this->beta.Size());
					Vector<double> variance = this->covariance_model->CoefficientsVariance();
					const int nvars = this->variables.Size();
					for (int i = 0, ik = 0; i < nvars; ++i)
					{
						const Vector<double> & v = this->beta.Value(i);
						for (int k = 0; k < v.Size(); ++k, ++ik)
							estimates(ik) = Estimate(v(k), variance(ik));
					}
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
						this->variables(j)->UpdatePredictor(eta, this->beta.Value(j), this->factor);
				}

				int Block::Update(const Vector<double> & weights, const Vector<double> & values, Comparer comparer)
				{
					const int nvars = this->variables.Size();
					TriangularMatrix<Vector<double> >precision(nvars);
					Vector<Vector<double> > jacobian(nvars);
					for (int j = 0; j < nvars; ++j)
					{
						// Evaluate jacobian (return value optimization)
						Vector<double> jacobian_j = Variables::ScalarProduct(this->variables(j), values, this->factor);
						Move(jacobian(j), jacobian_j);
						for (int k = 0; k <= j; ++k)
						{
							// Evaluate precision (return value optimization)
							Vector<double> precision_jk =  Variables::ScalarProduct(this->variables(j), weights, this->variables(k), this->factor);
							Move(precision(j, k), precision_jk);
						}
					}

					this->covariance_model->Decompose(precision);
					int update = 0;
					update += this->beta.Update(jacobian, this->covariance_model, comparer);
					update += this->covariance_model->Update(this->beta.Values(), comparer);
					this->covariance_model->Decompose(precision);
					return update;
				}
			}
		}
	}
}
