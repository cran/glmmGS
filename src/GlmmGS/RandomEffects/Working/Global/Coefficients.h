#ifndef GLMMGS_RANDOMEFFECTS_WORKING_GLOBAL_COEFFICIENTS_H
#define GLMMGS_RANDOMEFFECTS_WORKING_GLOBAL_COEFFICIENTS_H

#include "../../../Standard.h"
#include "CovarianceModels/ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Global
			{
				// Coefficients
				class Coefficients
				{
				private:
					// Fields
					Vector<double> values;

				public:
					// Construction
					Coefficients(int size);
					~Coefficients();

					// Properties
					int Size() const;
					double Value(int i) const;
					const Vector<double> & Values() const;

					// Methods
					int Update(const Vector<double> & jacobian, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Comparer comparer);
				};

				// Definition
				inline
				int Coefficients::Size() const
				{
					return this->values.Size();
				}

				inline
				double Coefficients::Value(int i) const
				{
					return this->values(i);
				}

				inline
				const Vector<double> & Coefficients::Values() const
				{
					return this->values;
				}
			}
		}
	}
}

#endif
