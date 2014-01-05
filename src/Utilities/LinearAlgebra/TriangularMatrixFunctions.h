#ifndef UTILITIES_LINEARALGEBRA_TRIANGULARMATRIXFUNCTIONS_H
#define UTILITIES_LINEARALGEBRA_TRIANGULARMATRIXFUNCTIONS_H

#include "../Utilities.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// Operators
		TriangularMatrix<double> & operator *=(TriangularMatrix<double> & A, double a);
		TriangularMatrix<double> & operator +=(TriangularMatrix<double> & A, const TriangularMatrix<double> & B);
		TriangularMatrix<double> & operator -=(TriangularMatrix<double> & A, const TriangularMatrix<double> & B);
		TriangularMatrix<double> operator +(TriangularMatrix<double> & A, const TriangularMatrix<double> & B);
		TriangularMatrix<double> operator -(TriangularMatrix<double> & A, const TriangularMatrix<double> & B);
		TriangularMatrix<double> operator *(double a, const TriangularMatrix<double> & A);

		// Functions
		Vector<double> Diagonal(const TriangularMatrix<double> & A);
		double Trace(const TriangularMatrix<double> & A);
		double SquareTrace(const TriangularMatrix<double> & A);

		// Conversion
		Matrix<double> ToLower(const TriangularMatrix<double> & A);
		Matrix<double> ToUpper(const TriangularMatrix<double> & A);
		Matrix<double> ToSymmetric(const TriangularMatrix<double> & A);

		// Vectorial functions
		int TotalSize(const TriangularMatrix<Vector<double> > & x);
	}
}

#endif
