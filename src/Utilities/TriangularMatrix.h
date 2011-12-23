#pragma once

#include "Container.h"
#include "Exceptions/Assertions.h"

namespace Utilities
{
	// TriangularMatrix
	template <class TYPE>
	class TriangularMatrix : public Container<TYPE>
	{
	private:
		// Fields
		int nrows;
		
		// Helper
		static int Base(int row);
	public:
		// Column class
		class Column
		{
		private:
			const TriangularMatrix<TYPE> & matrix;
			int column;
		public:
			Column(const TriangularMatrix<TYPE> & matrix, int column) : matrix(matrix), column(column) {}
			int Size() const {return this->matrix.NumberOfRows();}
			int Element(int index) const {return this->matrix.Element(index, column);}
		};

		// Construction
		TriangularMatrix();
		TriangularMatrix(int nrows);

		// Attributes
		int NumberOfRows() const;

		// Element access
		TYPE & operator ()(int i, int j);
		const TYPE & operator ()(int i, int j) const;
		TYPE & Element(int i, int j);
		const TYPE & Element(int i, int j) const;

		// Row/Column access
		Column Column(int column) const;

		// Assignment
		const TriangularMatrix<TYPE> & operator =(const TYPE & x);

		// Memory
		void Size(int nrows);
		void Free();
	};

	// Construction
	template <class TYPE> inline
	TriangularMatrix<TYPE>::TriangularMatrix()
		: nrows(0)
	{
	}

	template <class TYPE> inline
	TriangularMatrix<TYPE>::TriangularMatrix(int nrows)
		: Container<TYPE>(TriangularMatrix::Base(nrows)), nrows(nrows)
	{
	}

	// Attributes
	template <class TYPE> inline
	int TriangularMatrix<TYPE>::NumberOfRows() const
	{
		return this->nrows;
	}

	// Element access
	template <class TYPE> inline
	TYPE & TriangularMatrix<TYPE>::operator ()(int i, int j)
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j <= i);
		return this->ptr[TriangularMatrix::Base(i) + j];
	}

	template <class TYPE> inline
	const TYPE & TriangularMatrix<TYPE>::operator ()(int i, int j) const
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j <= i);
		return this->ptr[TriangularMatrix::Base(i) + j];
	}

	template <class TYPE> inline
	TYPE & TriangularMatrix<TYPE>::Element(int i, int j)
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j <= i);
		return this->ptr[TriangularMatrix::Base(i) + j];
	}

	template <class TYPE> inline
	const TYPE & TriangularMatrix<TYPE>::Element(int i, int j) const
	{
		_ASSERT_ARGUMENT(i >= 0 && i < this->nrows && j >= 0 && j <= i);
		return this->ptr[TriangularMatrix::Base(i) + j];
	}

	// Column access
	template <class TYPE> inline
	class TriangularMatrix<TYPE>::Column TriangularMatrix<TYPE>::Column(int col) const
	{
		_ASSERT_ARGUMENT(col >= 0.0 && col < this->nrows);
		class TriangularMatrix<TYPE>::Column column(*this, col);
		return column;
	}

	// Assignment
	template <class TYPE>
	const TriangularMatrix<TYPE> & TriangularMatrix<TYPE>::operator =(const TYPE & x)
	{
		int size = TriangularMatrix::Base(this->nrows);
		for (int i = 0; i < size; ++i)
			this->ptr[i] = x;
		return *this;
	}

	// Memory
	template <class TYPE>
	void TriangularMatrix<TYPE>::Size(int nrows)
	{
		Container<TYPE>::Allocate(TriangularMatrix::Base(nrows));
		this->nrows = nrows;
	}

	template <class TYPE>
	void TriangularMatrix<TYPE>::Free()
	{
		Container<TYPE>::Free();
		this->nrows = 0;
	}

	template <class TYPE> inline
	int TriangularMatrix<TYPE>::Base(int row)
	{
		return (row * (row + 1)) >> 1;
	}
}
