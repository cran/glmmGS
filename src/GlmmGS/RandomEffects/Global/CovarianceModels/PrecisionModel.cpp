#include "../../../Standard.h"
#include "../../Working/Global/CovarianceModels/ICovarianceModel.h"
#include "../../Working/Global/CovarianceModels/PrecisionModel.h"
#include "PrecisionModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Global
		{
			namespace CovarianceModels
			{
				// Construction
				PrecisionModel::PrecisionModel(WeakMatrix<const double> precision)
					: precision(precision)
				{
				}

				PrecisionModel::~PrecisionModel()
				{
				}

				// Implementation
				Pointer<Working::Global::CovarianceModels::ICovarianceModel> PrecisionModel::CreateWorking() const
				{
					typedef Working::Global::CovarianceModels::PrecisionModel T;
					return Pointer<T>(new(bl) T(this->precision));
				}
			}
		}
	}
}
