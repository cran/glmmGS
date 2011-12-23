#pragma once

#include "Container.h"
#include "Exceptions/Assertions.h"

namespace Utilities
{
	// Vector
	template <class TYPE> 
	class Vector : public Container<TYPE>
	{
	private:
		// Fields
		int size;

	public:
		// Construction
		Vector();
		explicit Vector(int size);

		// Attributes
		int Size() const;

		// Element access
		TYPE & operator ()(int index);
		TYPE & Element(int index);
		const TYPE & operator ()(int index) const;
		const TYPE & Element(int index) const;
		
		// Assignment
		const Vector<TYPE> & operator =(const TYPE & x);

		// Memory
		void Size(int size);
		void Resize(int size);
		void Free();
		void FreeExtra();

		// Manipulation
		void Add(const TYPE & x);
		void Remove();
		void RemoveAll();
	};

	// Construction
	template <class TYPE> inline
	Vector<TYPE>::Vector()
		: size(0)
	{
	}

	template <class TYPE> inline
	Vector<TYPE>::Vector(int size)
		: Container<TYPE>(size), size(size)
	{
	}

	// Attributes
	template <class TYPE> inline
	int Vector<TYPE>::Size() const
	{
		return this->size;
	}

	// Element access
	template <class TYPE> inline
	TYPE & Vector<TYPE>::operator ()(int index)
	{
		_ASSERT_ARGUMENT(index >= 0 && index < this->size)
		return this->ptr[index];
	}

	template <class TYPE> inline
	TYPE & Vector<TYPE>::Element(int index)
	{
		_ASSERT_ARGUMENT(index >= 0 && index < this->size)
		return this->ptr[index];
	}

	template <class TYPE> inline
	const TYPE & Vector<TYPE>::operator ()(int index) const
	{
		_ASSERT_ARGUMENT(index >= 0 && index < this->size)
		return this->ptr[index];
	}

	template <class TYPE> inline
	const TYPE & Vector<TYPE>::Element(int index) const
	{
		_ASSERT_ARGUMENT(index >= 0 && index < this->size)
		return this->ptr[index];
	}
	
	// Assignment
	template <class TYPE>
	const Vector<TYPE> & Vector<TYPE>::operator =(const TYPE & x)
	{
		for (int i = 0; i < this->size; ++i)
			this->ptr[i] = x;
		return *this;
	}

	// Memory
	template <class TYPE>
	void Vector<TYPE>::Size(int size)
	{
		Container<TYPE>::Allocate(size);
		this->size = size;
	}

	template <class TYPE>
	void Vector<TYPE>::Resize(int size)
	{
		Container<TYPE>::Reallocate(size);
		this->size = size;
	}
	
	template <class TYPE>
	void Vector<TYPE>::Free()
	{
		Container<TYPE>::Free();
		this->size = 0;
	}

	template <class TYPE>
	void Vector<TYPE>::FreeExtra()
	{
		Container<TYPE>::Reallocate(this->size);
	}

	// Manipulation
	template <class TYPE>
	void Vector<TYPE>::Add(const TYPE & x)
	{
		if (this->size == this->capacity)
		{
			TYPE y = x; // Copy in case x points to an element of the vector
			Container<TYPE>::Grow();
			this->ptr[this->size] = y;
			++this->size;
		}
		else
		{
			this->ptr[this->size] = x;
			++this->size;
		}
	}

	template <class TYPE>
	void Vector<TYPE>::Remove()
	{
		if (this->size > 0)
			--this->size;
	}

	template <class TYPE>
	void Vector<TYPE>::RemoveAll()
	{
		this->size = 0;
	}
}
