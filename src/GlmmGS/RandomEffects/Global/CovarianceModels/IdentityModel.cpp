#include "../../../Standard.h"
#include "../../Working/Global/CovarianceModels/ICovarianceModel.h"
#include "../../Working/Global/CovarianceModels/IdentityModel.h"
#include "IdentityModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Global
		{
			namespace CovarianceModels
			{
				// Construction
				IdentityModel::IdentityModel(int size)
					: size(size)
				{
				}

				IdentityModel::~IdentityModel()
				{
				}

				// Implementation
				Pointer<Working::Global::CovarianceModels::ICovarianceModel> IdentityModel::CreateWorking() const
				{
					typedef Working::Global::CovarianceModels::IdentityModel T;
					return Pointer<T>(new(bl) T(this->size));
				}
			}
		}
	}
}
