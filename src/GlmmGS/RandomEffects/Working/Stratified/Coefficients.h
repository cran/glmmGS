#pragma once

#include "../../../Standard.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "Boosters/IBooster.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				// Coefficients
				class Coefficients
				{
				private:
					// Fields
					int size;
					Vector<Vector<double> > values;
					Pointer<Boosters::IBooster> booster;

				public:
					// Construction
					Coefficients(int nvariables, int nlevels, Pointer<Boosters::IBooster> booster);
					~Coefficients();

					// Properties
					int Size() const;
					const Vector<double> & Value(int i) const;
					const Vector<Vector<double> > & Values() const;

					// Methods
					int Update(const Vector<Vector<double> > & jacobian, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Comparer comparer);
				};

				// Properties
				inline
				int Coefficients::Size() const
				{
					return size;
				}

				inline
				const Vector<double> & Coefficients::Value(int i) const
				{
					return this->values(i);
				}

				inline
				const Vector<Vector<double> > & Coefficients::Values() const
				{
					return this->values;
				}
			}
		}
	}
}
