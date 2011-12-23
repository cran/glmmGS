#include "Comparer.h"
#include "Vector.h"
#include "Exceptions/Assertions.h"
#include <math.h>

namespace Utilities
{
	Comparer::Comparer(double relative_tolerance, double absolute_tolerance)
		: relative_tolerance(relative_tolerance), absolute_tolerance(absolute_tolerance)
	{
	}

	bool Comparer::AreEqual(double x, double y) const
	{
		const double aeps = fabs(x - y);
		const double asum = 0.5 * (fabs(x) + fabs(y));
		return aeps <= Max(this->relative_tolerance * asum, this->absolute_tolerance);
	}

	bool Comparer::IsZero(double eps, double x) const
	{
		return fabs(eps) <= Max(this->relative_tolerance * fabs(x), this->absolute_tolerance);
	}
}
