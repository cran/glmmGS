#pragma once

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
				// PrecisionModel
				class PrecisionModel : public ICovarianceModel
				{
				private:
					// Fields
					WeakMatrix<const double> precision;

					// Implementation
					Pointer<Working::Global::CovarianceModels::ICovarianceModel> CreateWorking() const;

				public:
					// Construction
					PrecisionModel(WeakMatrix<const double> precision);
					~PrecisionModel();
				};
			}
		}
	}
}
