#include "../../../Standard.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "Coefficients.h"
#include "Boosters/IBooster.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				// Construction
				Coefficients::Coefficients(int nvariables, int nlevels, Pointer<Boosters::IBooster> booster)
					: size(nvariables * nlevels), values(nvariables), booster(booster)
				{
					for (int i = 0; i < nvariables; ++i)
						this->values(i).Size(nlevels);
				}

				Coefficients::~Coefficients()
				{
				}

				// Methods
				int Coefficients::Update(const Vector<Vector<double> > & jacobian, const Pointer<CovarianceModels::ICovarianceModel> covariance_model, Comparer comparer)
				{
					// Re-parameterize coefficients
					this->booster->Reparameterize(this->values(0));

					// Evaluate update
					Vector<Vector<double> > h = covariance_model->CoefficientsUpdate(jacobian, this->values);

					// Re-parameterize updates
					this->booster->Reparameterize(h(0));

					// Check if update is significant
					const int update = comparer.IsZero(h, this->values) ? 0 : 1;

					// Debug
					Print("MaxAbs update random effects: %g\n", MaxAbs(h));

					// Update
					for (int i = 0; i < h.Size(); ++i)
						this->values(i) += h(i);

					return update;
				}
			}
		}
	}
}
