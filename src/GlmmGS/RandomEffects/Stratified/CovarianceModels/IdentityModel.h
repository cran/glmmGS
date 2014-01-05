#ifndef GLMMGS_RANDOMEFFECTS_STRATIFIED_COVARIANCE_MODELS_IDENTITYMODEL_H
#define GLMMGS_RANDOMEFFECTS_STRATIFIED_COVARIANCE_MODELS_IDENTITYMODEL_H

#include "../../../Standard.h"
#include "../../Working/Stratified/CovarianceModels/ICovarianceModel.h"
#include "ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Stratified
		{
			namespace CovarianceModels
			{
				// IdentityModel
				class IdentityModel : public ICovarianceModel
				{
				private:
					// Fields
					int nvars;
					int nlevels;

					// Implementation
					Pointer<Working::Stratified::CovarianceModels::ICovarianceModel> CreateWorking() const;

				public:
					// Construction
					IdentityModel(int nvars, int nlevels);
					~IdentityModel();
				};
			}
		}
	}
}

#endif
