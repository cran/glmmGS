#ifndef UTILITIES_IO_PRINT_H
#define UTILITIES_IO_PRINT_H

#include "../Vector.h"
#include "../TriangularMatrix.h"
#include "../WeakMatrix.h"
#include "BasicPrint.h"

namespace Utilities
{
	namespace IO
	{
		// Declaration
		template <class TYPE> void Print(const char * format, const Vector<TYPE> & values);
		template <class TYPE> void Print(const char * format, const Vector<Vector<TYPE> > & values);
		template <class TYPE> void Print(const char * format, const WeakMatrix<TYPE> matrix);
		template <class TYPE> void Print(const char * format, const TriangularMatrix<TYPE> & matrix);

		// Definition
		template <class TYPE>
		void Print(const char * format, const Vector<TYPE> & values)
		{
			for (int j = 0; j < values.Size(); ++j)
				Print(format, values(j));
		}

		template <class TYPE>
		void Print(const char * format, const Vector<Vector<TYPE> > & values)
		{
			for (int j = 0; j < values.Size(); ++j)
				Print(format, values(j));
		}

		template <class TYPE>
		void Print(const char * format, const WeakMatrix<TYPE> matrix)
		{
			for (int i = 0; i < matrix.NumberOfRows(); ++i)
			{
				const int m = matrix.NumberOfColumns() - 1;
				for (int j = 0; j < m; ++j)
				{
					Print(format, matrix(i, j));
					Print(" ");
				}
				Print(format, matrix(i, i));
				Print("\n");
			}
		}

		template <class TYPE>
		void Print(const char * format, const TriangularMatrix<TYPE> & matrix)
		{
			for (int i = 0; i < matrix.NumberOfRows(); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					Print(format, matrix(i, j));
					Print(" ");
				}
				Print(format, matrix(i, i));
				Print("\n");
			}
		}
	}
}

#endif
