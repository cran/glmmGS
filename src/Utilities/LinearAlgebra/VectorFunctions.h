#ifndef UTILITIES_LINEARALGEBRA_VECTORFUNCTIONS_H
#define UTILITIES_LINEARALGEBRA_VECTORFUNCTIONS_H

#include "../Utilities.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// Operators
		Vector<double> & operator *=(Vector<double> & v, double a);
		Vector<double> & operator +=(Vector<double> & v, const Vector<double> & w);
		Vector<double> & operator -=(Vector<double> & v, const Vector<double> & w);
		Vector<double> operator *(double a, const Vector<double> & v);
		Vector<double> operator +(const Vector<double> & v, const Vector<double> & w);
		Vector<double> operator -(const Vector<double> & v, const Vector<double> & w);

		// Functions
		double Sum(const Vector<double> & v);
		double ScalarProduct(const Vector<double> & v, const Vector<double> & w);
		double Square(const Vector<double> & v);
		double MaxAbs(const Vector<double> & v);
		double MinAbs(const Vector<double> & v);

		// Vectorial functions
		int TotalSize(const Vector<Vector<double> > & v);
		double ScalarProduct(const Vector<Vector<double> > & v, const Vector<Vector<double> > & w);
		double MaxAbs(const Vector<Vector<double> > & v);
		double MinAbs(const Vector<Vector<double> > & v);
	}
}

#endif
