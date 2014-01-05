#ifndef GLMMGS_OFFSETS_IOFFSET_H
#define GLMMGS_OFFSETS_IOFFSET_H

#include "../Standard.h"

namespace GlmmGS
{
	namespace Offsets
	{
		class IOffset
		{
		protected:
			// Construction
			IOffset();
		public:
			virtual ~IOffset();

			// Methods
			virtual void InitializePredictor(Vector<double> & eta) const = 0;
		};
	}
}

#endif
