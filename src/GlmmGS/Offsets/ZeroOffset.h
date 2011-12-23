#pragma once

#include "../Standard.h"
#include "IOffset.h"

namespace GlmmGS
{
	namespace Offsets
	{
		class ZeroOffset : public IOffset
		{
		public:
			// Construction
			ZeroOffset();
			~ZeroOffset();

			// Methods
			void InitializePredictor(Vector<double> & eta) const;
		};
	}
}
