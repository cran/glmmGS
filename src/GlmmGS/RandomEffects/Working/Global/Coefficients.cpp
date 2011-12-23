#include "../../../Standard.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "Coefficients.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Global
			{
				Coefficients::Coefficients(int size) :
					values(size)
				{
				}

				Coefficients::~Coefficients()
				{
				}

				int Coefficients::Update(const Vector<double> & jacobian, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Comparer comparer)
				{
					// Evaluate update
					Vector<double> h = covariance_model->CoefficientsUpdate(jacobian, this->values);

					// Debug
					Print("MaxAbs update random effects: %g\n", MaxAbs(h));

					// Check if update is significant
					const int update = comparer.IsZero(h, this->values) ? 0 : 1;

					// Update
					this->values += h;

					return update;
				}
			}
		}
	}
}
