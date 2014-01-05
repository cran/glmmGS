#ifndef UTILITIES_LINEARALGEBRA_VECTORIALCHOLESKYDECOMPOSITION_H
#define UTILITIES_LINEARALGEBRA_VECTORIALCHOLESKYDECOMPOSITION_H

#include "../Utilities.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// VectorialCholeskyDecomposition
		class VectorialCholeskyDecomposition
		{
		private:
			// Fields
			TriangularMatrix<Vector<double> > lower;
		
		public:
			// Construction
			VectorialCholeskyDecomposition();
			explicit VectorialCholeskyDecomposition(const TriangularMatrix<Vector<double> > & A);

			// Properties
			const TriangularMatrix<Vector<double> > & Lower() const;

			// Methods
			void Decompose(const TriangularMatrix<Vector<double> > & A);
			Vector<Vector<double> > Solve(const Vector<Vector<double> > & b) const;
			TriangularMatrix<Vector<double> > Inverse() const;
			double Determinant() const;
		};

		// Properties
		inline
		const TriangularMatrix<Vector<double> > & VectorialCholeskyDecomposition::Lower() const
		{
			return this->lower;
		}
	}
}

#endif
