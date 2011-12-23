#include "../../../Standard.h"
#include "../../Working/Stratified/CovarianceModels/ICovarianceModel.h"
#include "../../Working/Stratified/CovarianceModels/PrecisionModel.h"
#include "PrecisionModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Stratified
		{
			namespace CovarianceModels
			{
				// Construction
				PrecisionModel::PrecisionModel(int nvars, WeakMatrix<const double> precision)
					: nvars(nvars), precision(precision)
				{
				}

				PrecisionModel::~PrecisionModel()
				{
				}

				// Implementation
				Pointer<Working::Stratified::CovarianceModels::ICovarianceModel> PrecisionModel::CreateWorking() const
				{
					typedef Working::Stratified::CovarianceModels::PrecisionModel T;
					return Pointer<T>(new(bl) T(this->nvars, this->precision));
				}
			}
		}
	}
}
