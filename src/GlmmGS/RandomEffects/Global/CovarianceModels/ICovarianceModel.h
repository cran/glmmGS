#pragma once

#include "../../../Standard.h"
#include "../../Working/Global/CovarianceModels/ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Global
		{
			namespace CovarianceModels
			{
				// CovarianceModel
				class ICovarianceModel
				{
				public:
					// Construction
					ICovarianceModel();
					virtual ~ICovarianceModel();

					// Methods
					virtual Pointer<Working::Global::CovarianceModels::ICovarianceModel> CreateWorking() const = 0;
				};
			}
		}
	}
}
