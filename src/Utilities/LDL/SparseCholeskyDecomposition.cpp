#include "../Utilities.h"
#include "../Exceptions/Exceptions.h"
#include "../NewTypes/NewTypes.h"
#include "SparseCholeskyDecomposition.h"
#include "SparseMatrix.h"

#include "Internal/ldl.h"
#include "Internal/amd.h"

namespace Utilities 
{
	namespace LDL
	{
		using namespace Utilities::NewTypes;

		SparseCholeskyDecomposition::SparseCholeskyDecomposition()
		{
		}

		void SparseCholeskyDecomposition::Decompose(const SparseMatrix<double> upper)
		{
			// Computes lower triangular matrix such that L D L^T = U

			const int ncols = upper.NumberOfColumns();

			// Allocate permutations
			this->permutation = NewTypes::Vector<int>(ncols);
			this->permutation_inverse = NewTypes::Vector<int>(ncols);

			// Find permutation
			int amd_retval = amd_order(ncols,
					Cast<const Array<int> >(upper.Counts()).pointer(),
					Cast<const Array<int> >(upper.Indices()).pointer(),
					Cast<const Array<int> >(this->permutation).pointer(),
					NULL,
					NULL);

			if (amd_retval == AMD_INVALID || amd_retval == AMD_OUT_OF_MEMORY)
				throw Exceptions::NumericException("AMD failed");

			// Symbolic decomposition
			NewTypes::Vector<int> lp(ncols + 1);
			Array<int> parent(ncols);
			Array<int> lnz(ncols);
			Array<int> flag(ncols);
			Array<int> null;

			Internal::LDL_symbolic(ncols,
					Cast<const Array<int> >(upper.Counts()),
					Cast<const Array<int> >(upper.Indices()),
					Cast<Array<int> >(lp),
					parent, lnz, flag,
					Cast<const Array<int> >(this->permutation),
					Cast<Array<int> >(this->permutation_inverse));

			// Numeric decomposition
			const int lsize = lp(ncols);
			NewTypes::Vector<double> lx(lsize);
			NewTypes::Vector<int> li(lsize);
			NewTypes::Vector<double> d(ncols);
			Array<double> y(ncols);
			Array<int> pattern(ncols);

			const int ldl_retval = Internal::LDL_numeric(ncols,
					Cast<const Array<int> >(upper.Counts()),
					Cast<const Array<int> >(upper.Indices()),
					Cast<const Array<double> >(upper.Values()),
					Cast<const Array<int> >(lp),
					parent, lnz,
					Cast<const Array<int> >(li),
					Cast<Array<double> >(lx),
					Cast<Array<double> >(d),
					y, pattern, flag,
					Cast<const Array<int> >(this->permutation),
					Cast<const Array<int> >(this->permutation_inverse));

			if (ldl_retval != ncols)
				throw Exceptions::Exception("LDL failed");

			// Set lower and diagonal matrices
			this->lower = SparseMatrix<double>(lx, li, lp);
			this->diagonal = d;
		}

		NewTypes::Vector<double> SparseCholeskyDecomposition::Solve(const NewTypes::Vector<double> b) const
		{
			_VALIDATE_ARGUMENT(b.Size() == this->lower.NumberOfColumns());

			const int n = this->diagonal.Size();

			// Permute b
			NewTypes::Vector<double> x(n);
			for (int j = 0; j < n ; ++j)
				x(j) = b(this->permutation(j));

			// Solve L x = b (the diagonal elements of L are assumed equal to 1)
			for (int j = 0; j < n; ++j)
			{
				const int p2 = this->lower.Count(j + 1);
				for (int p = this->lower.Count(j); p < p2; ++p)
					x(this->lower.Index(p)) -= this->lower.Value(p) * x(j);
			}

			// Solve D x = b
			for (int j = 0 ; j < n ; ++j)
				x(j) /= this->diagonal(j);

			// Solve L^T x = b
			for (int j = n - 1; j >= 0; --j)
			{
				const int p2 = this->lower.Count(j + 1);
				for (int p = this->lower.Count(j); p < p2; ++p)
					x(j) -= this->lower.Value(p) * x(this->lower.Index(p));
			}

			// Permute solution
			NewTypes::Vector<double> y(n);
			for (int j = 0; j < n ; ++j)
				y(this->permutation(j)) = x(j);

			return y;
		}

		/*
		TriangularMatrix<double> SparseCholeskyDecomposition::Inverse() const
		{
			const int n = this->diagonal.Size();
			TriangularMatrix<double> y(n);
			NewTypes::Vector<double> x(n);
			for (int i = 0; i < n; ++i)
			{
				// Prepare RHS vector
				Set(x, 0);
				x(i) = 1.0;

				// Solve L x = b (the diagonal elements of L are assumed equal to 1)
				for (int j = 0; j < n; ++j)
				{
					const int p2 = this->lower.Count(j + 1);
					for (int p = this->lower.Count(j); p < p2; ++p)
						x(this->lower.Index(p)) -= this->lower.Value(p) * x(j);
				}

				// Solve D x = b
				for (int j = 0 ; j < n ; ++j)
					x(j) /= this->diagonal(j);

				// Solve L^T x = b for j = n - 1, ..., i
				for (int j = n - 1; j >= i; --j)
				{
					const int p2 = this->lower.Count(j + 1);
					for (int p = this->lower.Count(j); p < p2; ++p)
						x(j) -= this->lower.Value(p) * x(this->lower.Index(p));

					// Store matrix element
					y(j, i) = x(j);
				}
			}

			return y;
		}
		*/

		/*
		double SparseCholeskyDecomposition::Determinant() const
		{
			const int n = this->lower.NumberOfRows();
			double det = 1.0;
			for (int j = 0; j < n; ++j)
				det *= this->lower.Diagonal(j);
			return det * det;
		}
		*/
	}
}
