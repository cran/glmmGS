#include "../Utilities.h"
#include "../Math/Math.h"
#include "MatrixFunctions.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// Matrix
		Matrix<double> & operator *=(Matrix<double> & A, double a)
		{
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					A(i, j) *= a;
			return A;
		}

		Matrix<double> & operator +=(Matrix<double> & A, const Matrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == B.NumberOfColumns() && A.NumberOfRows() == B.NumberOfRows())
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					A(i, j) += B(i, j);
			return A;
		}

		Matrix<double> & operator -=(Matrix<double> & A, const Matrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == B.NumberOfColumns() && A.NumberOfRows() == B.NumberOfRows())
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					A(i, j) -= B(i, j);
			return A;
		}

		Matrix<double> operator *(double a, const Matrix<double> & A)
		{
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			Matrix<double> Y(m, n);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					Y(i, j) = a * A(i, j);
			return Y;
		}

		Vector<double> operator *(const Matrix<double> & A, const Vector<double> & v)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == v.Size())
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			Vector<double> y(m);
			for (int i = 0; i < m; ++i)
			{
				for (int j = 0; j < n; ++j)
					y(i) += A(i, j) * v(j);
			}
			return y;
		}

		Matrix<double> operator *(const Matrix<double> & A, const Matrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == B.NumberOfRows())
			int m = A.NumberOfRows();
			int n = B.NumberOfColumns();
			int l = A.NumberOfColumns();
			Matrix<double> C(m, n);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
				{
					for (int k = 0; k < l; ++k)
						C(i, j) += A(i, k) * B(k, j);
				}
			return C;
		}

		Matrix<double> operator +(const Matrix<double> & A, const Matrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == B.NumberOfColumns() && A.NumberOfRows() == B.NumberOfRows())
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			Matrix<double> C(m, n);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					C(i, j) = A(i, j) + B(i, j);
			return C;
		}

		Matrix<double> operator -(const Matrix<double> & A, const Matrix<double> & B)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == B.NumberOfColumns() && A.NumberOfRows() == B.NumberOfRows())
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			Matrix<double> C(m, n);
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
					C(i, j) = A(i, j) - B(i, j);
			return C;
		}

		Matrix<double> Transpose(const Matrix<double> & A)
		{
			int m = A.NumberOfRows();
			int n = A.NumberOfColumns();
			Matrix<double> Y(n, m);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < m; ++j)
					Y(i, j) = A(j, i);
			return Y;
		}

		Matrix<double> Identity(int n)
		{
			Matrix<double> I(n, n);
			for (int i = 0; i < n; ++i)
				I(i, i) = 1.0;
			return I;
		}

		Matrix<double> Diagonal(const Vector<double> & v)
		{
			int n = v.Size();
			Matrix<double> A(n, n);
			A = 0.0;
			for (int i = 0; i < n; ++i)
				A(i, i) = v(i);
			return A;
		}

		Vector<double> Diagonal(const Matrix<double> & A)
		{
			int n = A.NumberOfRows();
			Vector<double> v(n);
			for (int i = 0; i < n; ++i)
				v(i) = A(i, i);
			return v;
		}

		Vector<double> RowSums(const Matrix<double> & A)
		{
			Vector<double> y(A.NumberOfRows());
			for (int i = 0; i < A.NumberOfRows(); ++i)
				for (int j = 0; j < A.NumberOfColumns(); ++j)
					y(i) += A(i, j);
			return y;
		}

		Vector<double> ColumnSums(const Matrix<double> & A)
		{
			Vector<double> y(A.NumberOfColumns());
			for (int j = 0; j < A.NumberOfColumns(); ++j)
				for (int i = 0; i < A.NumberOfRows(); ++i)
					y(j) += A(i, j);
			return y;
		}
		
		double MaxAbs(const Matrix<double> & A)
		{
			double norm = 0.0;
			const int m = A.NumberOfRows();
			const int n = A.NumberOfColumns();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < n; ++j)
				{
					double a = fabs(A(i, j));
					if (a > norm)
						norm = a;
				}
			return norm;
		}

		double Trace(const Matrix<double> & A)
		{
			const int n = A.NumberOfRows();
			double tr = 0.0;
			for (int i = 0; i < n; ++i)
				tr += A(i, i);
			return tr;
		}

		TriangularMatrix<double> Lower(const Matrix<double> & A)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == A.NumberOfRows())
			const int n = A.NumberOfRows();
			TriangularMatrix<double> Y(n);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= i; ++j)
					Y(i, j) = A(i, j);
			return Y;
		}

		TriangularMatrix<double> Upper(const Matrix<double> & A)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == A.NumberOfRows())
			const int n = A.NumberOfRows();
			TriangularMatrix<double> Y(n);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= i; ++j)
					Y(i, j) = A(j, i);
			return Y;
		}

		TriangularMatrix<double> Symmetric(const Matrix<double> & A)
		{
			_ASSERT_ARGUMENT(A.NumberOfColumns() == A.NumberOfRows())
			const int n = A.NumberOfRows();
			TriangularMatrix<double> Y(n);
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= i; ++j)
					Y(i, j) = 0.5 * (A(i, j) + A(j, i));
			return Y;
		}
	}
}
