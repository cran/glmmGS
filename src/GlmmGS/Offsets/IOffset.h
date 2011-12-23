#pragma once

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
