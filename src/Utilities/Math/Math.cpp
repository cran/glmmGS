#include "../Exceptions/Exceptions.h"
#include "Math.h"
#include <limits.h>
namespace Utilities
{
	namespace Math
	{
		// Functions
		double Pythag(double a, double b)
		{
			double absa, absb;
			absa = fabs(a);
			absb = fabs(b);
			if (absa > absb) 
				return absa * sqrt(1.0 + Square(absb / absa));
			else 
				return (absb == 0.0 ? 0.0 : absb * sqrt(1.0 + Square(absa / absb)));
		}

		double LnGamma(double x)
		{
			static const double coeffs[6] =
			{
				76.18009172947146, 
				-86.50532032941677,
				24.01409824083091, 
				-1.231739572450155,
				0.1208650973866179e-2, 
				-0.5395239384953e-5
			};
			double y = x;
			double tmp = x + 5.5;
			tmp -= (x + 0.5) * log(tmp);
			double ser = 1.000000000190015;
			for (int j = 0; j < 6; j++) 
				ser += coeffs[j] / ++y;
			return -tmp + log(2.5066282746310005 * ser / x);
		}

		int Pow(int base, int n)
		{
			// Validate arguments
			_VALIDATE_ARGUMENT(base >= 0 && n >= 0);

			// Special cases
			if (base == 1 || n == 0) // by analytical continuation of the x^x function, 0^0 is set equal to 1
				return 1;

			// Calculate power
			static const double MAX = INT_MAX;
			double result = 1.0;
			for (double power = base; (power <= MAX) && (n != 0); power *= power, n >>= 1)
			{
				if ((n & 0x1) == 0x1)
					result *= power;
				// Check for overflow
				if (result > MAX)
					throw Exceptions::IntegerOverflowException();
			}

			// Check reminder of exponent for overflow
			if (n != 0)
				throw Exceptions::IntegerOverflowException();

			// It is safe to cast now
			return static_cast<int>(result);
		}

		// Vector functions
		Vector<double> Sqrt(const Vector<double> & x)
		{
			const int n = x.Size();
			Vector<double> y(n);
			for (int i = 0; i < n; ++i)
				y(i) = sqrt(x(i));
			return y;
		}
	}
}
