#include "../../../Standard.h"
#include "../../Working/Stratified/CovarianceModels/ICovarianceModel.h"
#include "../../Working/Stratified/CovarianceModels/IdentityModel.h"
#include "IdentityModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Stratified
		{
			namespace CovarianceModels
			{
				// Construction
				IdentityModel::IdentityModel(int nvars, int nlevels)
					: nvars(nvars), nlevels(nlevels)
				{
				}

				IdentityModel::~IdentityModel()
				{
				}

				// Implementation
				Pointer<Working::Stratified::CovarianceModels::ICovarianceModel> IdentityModel::CreateWorking() const
				{
					typedef Working::Stratified::CovarianceModels::IdentityModel T;
					return Pointer<T>(new(bl) T(this->nvars, this->nlevels));
				}
			}
		}
	}
}
