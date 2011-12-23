#pragma once

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
				// PrecisionModel
				class PrecisionModel : public ICovarianceModel
				{
				private:
					// Fields
					int nvars;
					WeakMatrix<const double> precision;

					// Implementation
					Pointer<Working::Stratified::CovarianceModels::ICovarianceModel> CreateWorking() const;

				public:
					// Construction
					PrecisionModel(int nvars, WeakMatrix<const double> precision);
					~PrecisionModel();
				};
			}
		}
	}
}
