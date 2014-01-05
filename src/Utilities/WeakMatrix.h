#ifndef UTILITIES_WEAKMATRIX_H
#define UTILITIES_WEAKMATRIX_H

#include "Exceptions/Assertions.h"
#include "WeakVector.h"
#include "IO/BasicPrint.h"

namespace Utilities
{
	template <class TYPE>
	class WeakMatrix
	{
	private:
		TYPE * ptr;
		int nrows;
		int ncols;

	public:
		// Construction
		WeakMatrix(TYPE * ptr, int nrows, int ncols);

		// Properties
		int NumberOfRows() const;
		int NumberOfColumns() const;

		// Element access
		TYPE & operator ()(int i, int j);
		const TYPE & operator ()(int i, int j) const;

		// Row access
		WeakVector<TYPE> Row(int i);
		WeakVector<const TYPE> Row(int i) const;
	};

	// Construction
	template <class TYPE>
	WeakMatrix<TYPE>::WeakMatrix(TYPE * ptr, int nrows, int ncols)
		: ptr(NULL), nrows(0), ncols(0)
	{
		if (ptr != NULL && nrows > 0 && ncols > 0)
		{
			this->ptr = ptr;
			this->nrows = nrows;
			this->ncols = ncols;
		}
		else
			throw Utilities::Exceptions::Exception("Invalid WeakMatrix");
	}

	// Properties
	template <class TYPE> inline
	int WeakMatrix<TYPE>::NumberOfRows() const
	{
		return this->nrows;
	}

	template <class TYPE> inline
	int WeakMatrix<TYPE>::NumberOfColumns() const
	{
		return this->ncols;
	}

	// Element access
	template <class TYPE> inline
	TYPE & WeakMatrix<TYPE>::operator ()(int i, int j)
	{
		_ASSERT_ARGUMENT(0 <= i && i < this->nrows && 0 <= j && j < this->ncols);
		return this->ptr[this->ncols * i + j];
	}

	template <class TYPE> inline
	const TYPE & WeakMatrix<TYPE>::operator ()(int i, int j) const
	{
		_ASSERT_ARGUMENT(0 <= i && i < this->nrows && 0 <= j && j < this->ncols);
		return this->ptr[this->ncols * i + j];
	}

	// Row access
	template <class TYPE> inline
	WeakVector<TYPE> WeakMatrix<TYPE>::Row(int i)
	{
		_ASSERT_ARGUMENT(0 <= i && i < this->nrows);
		return WeakVector<TYPE>(this->ptr + this->ncols * i, this->ncols);
	}

	template <class TYPE> inline
	WeakVector<const TYPE> WeakMatrix<TYPE>::Row(int i) const
	{
		_ASSERT_ARGUMENT(0 <= i && i < this->nrows);
		return WeakVector<TYPE>(this->ptr + this->ncols * i, this->ncols);
	}
}

#endif
