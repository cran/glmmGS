#ifndef UTILITIES_LINEARALGEBRA_MATRIXFUNCTIONS_H
#define UTILITIES_LINEARALGEBRA_MATRIXFUNCTIONS_H

#include "../Utilities.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// Operators
		Matrix<double> & operator *=(Matrix<double> & A, double a);
		Matrix<double> & operator +=(Matrix<double> & A, const Matrix<double> & B);
		Matrix<double> & operator -=(Matrix<double> & A, const Matrix<double> & B);
		Matrix<double> operator *(double a, const Matrix<double> & A);
		Vector<double> operator *(const Matrix<double> & A, const Vector<double> & v);
		Matrix<double> operator *(const Matrix<double> & A, const Matrix<double> & B);
		Matrix<double> operator +(const Matrix<double> & A, const Matrix<double> & B);
		Matrix<double> operator -(const Matrix<double> & A, const Matrix<double> & B);

		// Functions
		Matrix<double> Transpose(const Matrix<double> & A);
		Matrix<double> Identity(int n);
		Matrix<double> Diagonal(const Vector<double> & v);
		Vector<double> Diagonal(const Matrix<double> & A);
		Vector<double> RowSums(const Matrix<double> & A);
		Vector<double> ColumnSums(const Matrix<double> & A);
		double MaxAbs(const Matrix<double> & A);
		double Trace(const Matrix<double> & A);

		// Conversions
		TriangularMatrix<double> Lower(const Matrix<double> & A);
		TriangularMatrix<double> Upper(const Matrix<double> & A);
		TriangularMatrix<double> Symmetric(const Matrix<double> & A);
	}
}

#endif
