#include "VectorialCholeskyDecomposition.h"
#include "../Exceptions/Exceptions.h"
#include "../Math/Math.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		VectorialCholeskyDecomposition::VectorialCholeskyDecomposition()
		{
		}

		VectorialCholeskyDecomposition::VectorialCholeskyDecomposition(const TriangularMatrix<Vector<double> > & A)
		{
			this->Decompose(A);
		}
		
		void VectorialCholeskyDecomposition::Decompose(const TriangularMatrix<Vector<double> > & A)
		{
			this->lower = A;
			const int n = this->lower.NumberOfRows();
			
			// Computes lower triangular Matrix such that L * Transpose(L) = A
			for (int i = 0; i < n; ++i)
			{
				Vector<double> & diag = this->lower(i, i);
				// j == i
				{
					Vector<double> sum = diag;
					const int L = sum.Size();
					for (int k = i - 1; k >= 0; --k) 
						for (int l = 0; l < L; ++ l)
							sum(l) -= Math::Square(this->lower(i, k)(l));
					// Update diagonal elements
					for (int l = 0; l < L; ++ l)
					{
						if (sum(l) <= 0.0)
							throw Exceptions::NumericException("Non positive matrix in vectorial Cholesky decomposition");
						diag(l) = sqrt(sum(l));
					}
				}
				// j > i
				for (int j = i + 1; j < n; ++j)
				{
					Vector<double> sum = this->lower(j, i);
					const int L = sum.Size();
					for (int k = i - 1; k >= 0; --k) 
						for (int l = 0; l < L; ++ l)
							sum(l) -= this->lower(i, k)(l) * this->lower(j, k)(l);
					// Update off diagonal elements
					for (int l = 0; l < L; ++ l)
						this->lower(j, i)(l) = sum(l) / diag(l);
				}
			}
		}
		
		Vector<Vector<double> > VectorialCholeskyDecomposition::Solve(const Vector<Vector<double> > & b) const
		{
			_ASSERT_ARGUMENT(b.Size() == this->lower.NumberOfRows())
			const int n = this->lower.NumberOfRows();
			Vector<Vector<double> > x(n);
			
			// Back-substitution algorithm
			for (int i = 0; i < n; ++i)
			{
				const Vector<double> & diag = this->lower(i, i);
				Vector<double> sum = b(i);
				const int L = sum.Size();
				for (int k = i - 1; k >= 0; --k)
					for (int l = 0; l < L; ++l)
						sum(l) -= this->lower(i, k)(l) * x(k)(l);
				x(i).Size(L);
				for (int l = 0; l < L; ++l)
					x(i)(l) = sum(l) / diag(l);
			}
			for (int i = n - 1; i >= 0; --i)
			{
				const Vector<double> & diag = this->lower(i, i);
				Vector<double> sum = x(i);
				const int L = sum.Size();
				for (int k = i + 1; k < n; ++k)
					for (int l = 0; l < L; ++l)
						sum(l) -= this->lower(k, i)(l) * x(k)(l);
				for (int l = 0; l < L; ++l)
					x(i)(l) = sum(l) / diag(l);
			}
			return x;
		}

		TriangularMatrix<Vector<double> > VectorialCholeskyDecomposition::Inverse() const
		{
			const int n = this->lower.NumberOfRows();
			TriangularMatrix<Vector<double> > X(n);

			// Calculate inverse
			for (int j = 0; j < n; ++j)
			{
				// Back-substitution algorithm with b = delta(j)
				for (int i = j; i < n; ++i)
				{
					const Vector<double> & diag = this->lower(i, i);
					const int L = diag.Size();
					Vector<double> sum(L);
					if (i == j)
						sum = 1.0;
					for (int k = i - 1; k >= j; --k)
						for (int l = 0; l < L; ++l)
							sum(l) -= this->lower(i, k)(l) * X(k, j)(l);
					X(i, j).Size(L);
					for (int l = 0; l < L; ++l)
						X(i, j)(l) = sum(l) / diag(l);
				}
				for (int i = n - 1; i >= j; --i)
				{
					const Vector<double> & diag = this->lower(i, i);
					const int L = diag.Size();
					Vector<double> sum = X(i, j);
					for (int k = i + 1; k < n; ++k)
						for (int l = 0; l < L; ++l)
							sum(l) -= this->lower(k, i)(l) * X(k, j)(l);
					for (int l = 0; l < L; ++l)
						X(i, j)(l) = sum(l) / diag(l);
				}
			}
			return X;
		}

		double VectorialCholeskyDecomposition::Determinant() const
		{
			const int n = this->lower.NumberOfRows();
			double det = 1.0;
			for (int j = 0; j < n; ++j)
			{
				const Vector<double> & diag = this->lower(j, j);
				const int L = diag.Size();
				for (int l = 0; l < L; ++l)
					det *= diag(l);
			}
			return det * det;
		}
	}
}
