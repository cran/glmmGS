#include "../Exceptions/Assertions.h"
#include "Vector.h"
#include "Matrix.h"
#include "../Vector.h"
#include "../TriangularMatrix.h"
#include "../LinearAlgebra/VectorFunctions.h"
#include "../LinearAlgebra/TriangularMatrixFunctions.h"
#include "../Math/Math.h"

namespace Utilities
{
	namespace NewTypes
	{
		// Specific copy-function

		// Copy vector
		void Copy(NewTypes::Vector<double> & dst, const Utilities::Vector<double> & src)
		{
			_ASSERT_ARGUMENT(dst.Size() == src.Size());
			for (int i = 0; i < dst.Size(); ++i)
				dst(i) = src(i);
		}

		// Copy vector
		void Copy(NewTypes::Vector<double> & dst, const Utilities::Vector<Utilities::Vector<double> > & src)
		{
			_ASSERT_ARGUMENT(dst.Size() == LinearAlgebra::TotalSize(src));
			for (int i = 0, ik = 0; i < src.Size(); ++i)
			{
				const Utilities::Vector<double> v = src(i);
				for (int k = 0; k < v.Size(); ++k, ++ik)
					dst(ik) = v(k);
			}
		}

		// Copy Matrices
		void Copy(NewTypes::Matrix<double> & dst, const Utilities::TriangularMatrix<double> & src)
		{
			_ASSERT_ARGUMENT(dst.NumberOfRows() == src.NumberOfRows() &&
					dst.NumberOfColumns() == src.NumberOfRows());

			const int n = src.NumberOfRows();
			for (int i = 0; i < n; ++i)
			{
				dst(i, i) = src(i, i);
				for (int j = 0; j < i; ++i)
					dst(i, j) = dst(j, i) = src(i, j);
			}
		}

		// Copy Matrices
		void Copy(NewTypes::Vector<double> & dst, const Utilities::TriangularMatrix<Utilities::Vector<double> > & src)
		{
			_ASSERT_ARGUMENT(dst.Size() == src.NumberOfRows() * LinearAlgebra::TotalSize(src));

			const int n = src.NumberOfRows();
			for (int i = 0, index = 0; i < n; ++i)
			{
				// Lower
				for (int j = 0; j <= i; ++j, ++index)
				{
					const Utilities::Vector<double> & v = src(i, j);
					for (int k = 0; k < v.Size(); ++k, ++index)
						dst(index) = v(k);
				}

				// Strictly upper
				for (int j = i + 1; j < n; ++j, ++index)
				{
					const Utilities::Vector<double> & v = src(j, i);
					for (int k = 0; k < v.Size(); ++k, ++index)
						dst(index) = v(k);
				}
			}
		}
	}
}
