#include "../Utilities/Comparer.h"
#include "Controls.h"

namespace GlmmGS
{
	Controls::Controls(double relative_tolerance, double absolute_tolerance, int maxiter)
		: comparer(relative_tolerance, absolute_tolerance), maxiter(maxiter)
	{
	}
}
