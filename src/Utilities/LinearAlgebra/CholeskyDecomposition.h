#pragma once

#include "../Utilities.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// CholeskyDecomposition
		class CholeskyDecomposition
		{
		private:
			// Fields
			TriangularMatrix<double> lower;
		
		public:
			// Construction
			CholeskyDecomposition();
			explicit CholeskyDecomposition(const TriangularMatrix<double> & A);

			// Properties
			const TriangularMatrix<double> & Lower() const;

			// Methods
			void Decompose(const TriangularMatrix<double> & A);
			Vector<double> Solve(const Vector<double> & b) const;
			TriangularMatrix<double> Inverse() const;
			double Determinant() const;
		};

		// Properties
		inline
		const TriangularMatrix<double> & CholeskyDecomposition::Lower() const
		{
			return this->lower;
		}
	}
}
