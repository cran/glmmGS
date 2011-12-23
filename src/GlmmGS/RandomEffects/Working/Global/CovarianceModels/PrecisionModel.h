#pragma once

#include "../../../../Standard.h"
#include "../../../../Estimate.h"
#include "ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
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
						WeakMatrix<const double> R;
						CholeskyDecomposition beta_precision_chol;

						// Implementation
						Vector<double> CoefficientsVariance() const;
						void Decompose(const TriangularMatrix<double> & precision);
						int Update(const Vector<double> & beta, Comparer comparer);
						Vector<double> CoefficientsUpdate(const Vector<double> & jacobian, const Vector<double> & beta) const;

					public:
						// Construction
						PrecisionModel(WeakMatrix<const double> R);
						~PrecisionModel();
					};
				}
			}
		}
	}
}
