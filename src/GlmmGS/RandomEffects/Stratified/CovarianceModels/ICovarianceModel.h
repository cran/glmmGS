#ifndef GLMMGS_RANDOMEFFECTS_STRATIFIED_COVARIANCE_MODELS_ICOVARIANCEMODEL_H
#define GLMMGS_RANDOMEFFECTS_STRATIFIED_COVARIANCE_MODELS_ICOVARIANCEMODEL_H

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

#endif
