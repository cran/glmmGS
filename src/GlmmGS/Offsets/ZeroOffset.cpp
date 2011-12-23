#include "../Standard.h"
#include "ZeroOffset.h"

namespace GlmmGS
{
	namespace Offsets
	{
		// Construction
		ZeroOffset::ZeroOffset()
		{
		}

		ZeroOffset::~ZeroOffset()
		{
		}

		// Methods
		void ZeroOffset::InitializePredictor(Vector<double> & eta) const
		{
			eta = 0.0;
		}
	}
}
