#pragma once

#include "../../Standard.h"
#include "../../Estimate.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			// IBlock
			class IBlock
			{
			protected:
				// Construction
				IBlock();
			public:
				virtual ~IBlock();

				// Properties
				virtual Vector<Estimate> Coefficients() const = 0;
				virtual Vector<Estimate> CovarianceComponents() const = 0;

				// Methods
				virtual void UpdatePredictor(Vector<double> & eta) const = 0;
				virtual int Update(const Vector<double> & w, const Vector<double> & z, Comparer comparer) = 0;
			};
		}
	}
}
