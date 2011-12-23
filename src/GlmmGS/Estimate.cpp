#include "Estimate.h"

namespace GlmmGS
{
	Estimate::Estimate()
		: value(0.0), variance(0.0)
	{
	}

	Estimate::Estimate(double value, double variance)
		: value(value), variance(variance)
	{
	}
}
