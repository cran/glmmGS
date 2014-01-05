#ifndef UTILITIES_NEWTYPES_FUNCTIONS_H
#define UTILITIES_NEWTYPES_FUNCTIONS_H

#include "../Exceptions/Assertions.h"
#include "Vector.h"
#include "Matrix.h"
#include "../Vector.h"
#include "../TriangularMatrix.h"

namespace Utilities
{
	namespace NewTypes
	{
		// Copy vectors
		template <class TYPE>
		void Copy(NewTypes::Vector<TYPE> & dst, const NewTypes::Vector<TYPE> & src)
		{
			_ASSERT_ARGUMENT(dst.Size() == src.Size());
			for (int i = 0; i < dst.Size(); ++i)
				dst(i) = src(i);
		}

		// Vector assignment to a constant
		template <class TYPE>
		void Set(NewTypes::Vector<TYPE> & dst, const TYPE & x)
		{
			const int n = dst.Size();
			for (int i = 0; i < n; ++i)
				dst(i) = x;
		}

		// Specific functions
		void Copy(NewTypes::Vector<double> & dst, const Utilities::Vector<double> & src);
		void Copy(NewTypes::Vector<double> & dst, const Utilities::Vector<Utilities::Vector<double> > & src);
		void Copy(NewTypes::Matrix<double> & dst, const Utilities::TriangularMatrix<double> & src);
		void Copy(NewTypes::Vector<double> & dst, const Utilities::TriangularMatrix<Utilities::Vector<double> > & src);
	}
}

#endif
