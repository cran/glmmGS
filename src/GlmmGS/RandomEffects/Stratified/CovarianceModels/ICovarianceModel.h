#pragma once

#include "../../../Standard.h"
#include "../../Working/Stratified/CovarianceModels/ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Stratified
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
					virtual Pointer<Working::Stratified::CovarianceModels::ICovarianceModel> CreateWorking() const = 0;
				};
			}
		}
	}
}
