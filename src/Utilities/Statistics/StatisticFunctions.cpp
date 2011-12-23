#include "../Vector.h"

namespace Utilities
{
	namespace Statistics
	{
		double Mean(const Vector<double> & x)
		{
			_VALIDATE_ARGUMENT(x.Size() > 0);
			const int n = x.Size();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += x(i);
			return sum / static_cast<double>(n);
		}
	}
}
