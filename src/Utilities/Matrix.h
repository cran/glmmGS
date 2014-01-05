#ifndef UTILITIES_MATRIX_H
#define UTILITIES_MATRIX_H

#include "Container.h"
#include "Exceptions/Assertions.h"

namespace Utilities
{
	// Matrix
	template <class TYPE>
	class Matrix : public Container<TYPE>
	{
	private:
		// Fields
		int nrows;
		int ncols;

	public:
		// Construction
		Matrix();
		Matrix(int nrows, int ncols);

		// Attributes
		int NumberOfRows() const;
		int NumberOfColumns() const;

		// Element access
		TYPE & operator ()(int i, int j);
		const TYPE & operator ()(int i, int j) const;
		TYPE & Element(int i, int j);
		const TYPE & Element(int i, int j) const;

		// Assignment
		const Matrix<TYPE> & operator =(const TYPE & x);

		// Memory
		void Size(int nrows, int ncols);
		void FreeExtra();
		void Free();
	};

	// Construction
	template <class TYPE> inline
	Matrix<TYPE>::Matrix()
		: nrows(0), ncols(0)
	{
	}

	template <class TYPE> inline
	Matrix<TYPE>::Matrix(int nrows, int ncols)
		: Container<TYPE>(nrows * ncols), nrows(nrows), ncols(ncols)
	{
	}

	// Attributes
	template <class TYPE> inline
	int Matrix<TYPE>::NumberOfRows() const
	{
		return this->nrows;
	}

	template <class TYPE> inline
	int Matrix<TYPE>::NumberOfColumns() const
	{
		return this->ncols;
	}

	// Element access
	template <class TYPE> inline
	TYPE & Matrix<TYPE>::operator ()(int i, int j)
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j < this->ncols)
		return this->ptr[i * this->ncols + j];
	}

	template <class TYPE> inline
	const TYPE & Matrix<TYPE>::operator ()(int i, int j) const
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j < this->ncols)
		return this->ptr[i * this->ncols + j];
	}
	
	template <class TYPE> inline
	TYPE & Matrix<TYPE>::Element(int i, int j)
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j < this->ncols)
		return this->ptr[i * this->ncols + j];
	}

	template <class TYPE> inline
	const TYPE & Matrix<TYPE>::Element(int i, int j) const
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j < this->ncols)
		return this->ptr[i * this->ncols + j];
	}

	// Assignment
	template <class TYPE>
	const Matrix<TYPE> & Matrix<TYPE>::operator =(const TYPE & x)
	{
		int size = this->nrows * this->ncols;
		for (int i = 0; i < size; ++i)
			this->ptr[i] = x;
		return *this;
	}

	// Memory
	template <class TYPE>
	void Matrix<TYPE>::Size(int nrows, int ncols)
	{
		Container<TYPE>::Allocate(nrows * ncols);
		this->nrows = nrows;
		this->ncols = ncols;
	}

	template <class TYPE>
	void Matrix<TYPE>::Free()
	{
		Container<TYPE>::Free();
		this->nrows = 0;
		this->ncols = 0;
	}


	template <class TYPE>
	void Matrix<TYPE>::FreeExtra()
	{
		Container<TYPE>::Reallocate(this->nrows * this->ncols);
	}
}

#endif
