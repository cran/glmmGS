#pragma once

#include <float.h>
#include <math.h>
#include "../Vector.h"

namespace Utilities 
{
	namespace Math
	{
		// Constants
		const double PI = 3.1415926535897932384626433832795;

		// Functions
		double Abs(double x);
		double Sign(double a, double b);
		double Square(double x);
		double Cube(double x);
		double Pythag(double a, double b);
		double AntiLogit(double x);
		double LnGamma(double x);
		double Expm1(double x);
		int Pow(int base, int n);

		// Vector functions
		Vector<double> Sqrt(const Vector<double> & x);

		// Definition
		inline
		double Abs(double x)
		{
			return (x >= 0.0) ? x : -x;
		}
		
		inline
		double Sign(double a, double b) 
		{
			return b >= 0.0 ? Abs(a) : -Abs(a);
		}

		inline
		double Square(double x)
		{
			return x * x;
		}
		
		inline
		double Cube(double x)
		{
			return x * x * x;
		}
		
		inline
		double AntiLogit(double x)
		{
			return 1.0 / (exp(-x) + 1.0);
		}

		inline
		double Expm1(double x)
		{
			return fabs(x) < DBL_EPSILON ? x : (exp(x) - 1.0);
		}
	}
}
