#ifndef GLMMGS_RANDOMEFFECTS_GLOBAL_COVARIANCEMODEL_IDENTITYMODEL_H
#define GLMMGS_RANDOMEFFECTS_GLOBAL_COVARIANCEMODEL_IDENTITYMODEL_H

#include "../../../Standard.h"
#include "../../Working/Global/CovarianceModels/ICovarianceModel.h"
#include "ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Global
		{
			namespace CovarianceModels
			{
				// IdentityModel
				class IdentityModel : public ICovarianceModel
				{
				private:
					// Fields
					int size;

					// Implementation
					Pointer<Working::Global::CovarianceModels::ICovarianceModel> CreateWorking() const;

				public:
					// Construction
					IdentityModel(int size);
					~IdentityModel();
				};
			}
		}
	}
}

#endif
