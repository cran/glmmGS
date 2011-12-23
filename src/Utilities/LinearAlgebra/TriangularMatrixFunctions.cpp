#include "../Math/Math.h"
#include "MatrixFunctions.h"
#include "TriangularMatrixFunctions.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// Operators
		TriangularMatrix<double> & operator *=(TriangularMatrix<double> & A, double a)
		{
			int m = A.NumberOfRows();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					A(i, j) *= a;
			return A;
		}
		
		TriangularMatrix<double> & operator +=(TriangularMatrix<double> & A, const TriangularMatrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfRows() == B.NumberOfRows())
			const int m = A.NumberOfRows();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					A(i, j) += B(i, j);
			return A;
		}
		
		TriangularMatrix<double> & operator -=(TriangularMatrix<double> & A, const TriangularMatrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfRows() == B.NumberOfRows())
			const int m = A.NumberOfRows();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					A(i, j) -= B(i, j);
			return A;
		}
		
		TriangularMatrix<double> operator +(TriangularMatrix<double> & A, const TriangularMatrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfRows() == B.NumberOfRows())
			const int m = A.NumberOfRows();
			TriangularMatrix<double> Y(m);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					Y(i, j) = A(i, j) + B(i, j);
			return Y;

		}
		
		TriangularMatrix<double> operator -(TriangularMatrix<double> & A, const TriangularMatrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfRows() == B.NumberOfRows())
			const int m = A.NumberOfRows();
			TriangularMatrix<double> Y(m);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					Y(i, j) = A(i, j) - B(i, j);
			return Y;

		}

		TriangularMatrix<double> operator *(double a, const TriangularMatrix<double> & A)
		{
			int m = A.NumberOfRows();
			TriangularMatrix<double> B(m);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j <= i; ++j)
					B(i, j) = a * A(i, j);
			return B;
		}

		// Functions
		Vector<double> Diagonal(const TriangularMatrix<double> & A)
		{
			const int n = A.NumberOfRows();
			Vector<double> d(n);
			for (int i = 0; i < n; ++i)
				d(i) = A(i, i);
			return d;
		}

		double Trace(const TriangularMatrix<double> & A)
		{
			const int n = A.NumberOfRows();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += A(i, i);
			return sum;
		}

		double SquareTrace(const TriangularMatrix<double> & A)
		{
			const int n = A.NumberOfRows();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
			{
				sum += Math::Square(A(i, i));
				for (int j = 0; j < i; ++j)
					sum += 2.0 * Math::Square(A(i, j));
			}
			return sum;
		}

		// Conversion
		Matrix<double> ToLower(const TriangularMatrix<double> & A)
		{
			int n = A.NumberOfRows();
			Matrix<double> L(n, n);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= i; ++j)
					L(i, j) = A(i, j);
			return L;
		}

		Matrix<double> ToUpper(const TriangularMatrix<double> & A)
		{
			const int n = A.NumberOfRows();
			Matrix<double> U(n, n);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= i; ++j)
					U(j, i) = A(i, j);
			return U;
		}

		Matrix<double> ToSymmetric(const TriangularMatrix<double> & A)
		{
			const int n = A.NumberOfRows();
			Matrix<double> S(n, n);
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < i; ++j)
					S(i, j) = S(j, i) = A(i, j);
				S(i, i) = A(i, i);
			}
			return S;
		}

		// Vectorial functions
		int TotalSize(const TriangularMatrix<Vector<double> > & x)
		{
			const int n = x.NumberOfRows();
			int size = 0;
			for (int i = 0; i < n; ++i)
				size += x(i, i).Size();
			return size;
		}
	}
}
