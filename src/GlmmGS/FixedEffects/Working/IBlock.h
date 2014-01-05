#ifndef GLMMGS_FIXEDEFFECTS_WORKING_IBLOCK_H
#define GLMMGS_FIXEDEFFECTS_WORKING_IBLOCK_H

#include "../../Standard.h"
#include "../../Estimate.h"

namespace GlmmGS
{
	namespace FixedEffects
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

				// Methods
				virtual void UpdatePredictor(Vector<double> & eta) const = 0;
				virtual int UpdateCoefficients(const Vector<double> & w, const Vector<double> & z, Comparer comparer) = 0;
			};
		}
	}
}

#endif
