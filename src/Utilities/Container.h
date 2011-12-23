#pragma once

#include "Exceptions/Assertions.h"
#include "Exceptions/InvalidArgumentException.h"
#include "Allocator.h"
#include "Algorithms.h"
#include <memory.h>

namespace Utilities
{
	// Container
	template <class TYPE>
	class Container
	{
	protected:
		// Fields
		TYPE * ptr;
		int capacity;
		
		// Contstruction
		Container();
		Container(int capacity);
		Container(const Container<TYPE> & src);
		~Container();

		// Memory
		void Allocate(int capacity);
		void Reallocate(int capacity);
		void Grow(int index = 0);
		void Free();

		// Assignment
		const Container<TYPE> & operator =(const Container<TYPE> & src);

	public:
		// Memory
		void Reserve(int capacity);
	};

	// Construction
	template <class TYPE> inline 
	Container<TYPE>::Container()
		: ptr(NULL), capacity(0)
	{
	}

	template <class TYPE>
	Container<TYPE>::Container(int capacity)
		: ptr(Allocator<TYPE>::Allocate(capacity)), capacity(capacity)
	{
		// Validate capacity
		_VALIDATE_ARGUMENT(capacity >= 0);

		// Construct
		memset(this->ptr, 0, sizeof(TYPE) * this->capacity);
		Allocator<TYPE>::Construct(this->ptr, this->capacity);
	}

	template <class TYPE> inline
	Container<TYPE>::Container(const Container<TYPE> & src)
		: ptr(Allocator<TYPE>::Allocate(src.capacity)), capacity(src.capacity)
	{
		// Copy-construct
		Allocator<TYPE>::CopyConstruct(this->ptr, src.ptr, this->capacity);
	}

	template <class TYPE> inline 
	Container<TYPE>::~Container()
	{
		// Destroy all and delete binary buffer
		if (this->ptr != NULL)
		{
			Allocator<TYPE>::Destroy(this->ptr, this->capacity);
			Allocator<TYPE>::Free(this->ptr);
		}
	}

	// Memory
	template <class TYPE>
	void Container<TYPE>::Allocate(int capacity)
	{
		// Validate argument
		_VALIDATE_ARGUMENT(capacity >= 0)

		// Delete and destroy
		this->Free();

		// Allocate
		this->ptr = Allocator<TYPE>::Allocate(capacity);
		this->capacity = capacity;

		// Construct
		memset(this->ptr, 0, sizeof(TYPE) * this->capacity);
		Allocator<TYPE>::Construct(this->ptr, this->capacity);
	}

	template <class TYPE>
	void Container<TYPE>::Reallocate(int capacity)
	{
		// If capacity is the same return
		if (capacity == this->capacity)
			return;

		// Validate argument
		_VALIDATE_ARGUMENT(capacity >= 0)

		// If current capacity is zero allocate
		if (this->capacity == 0)
			this->Allocate(capacity);

		// Allocate
		TYPE * ptr = Allocator<TYPE>::Allocate(capacity);

		if (capacity < this->capacity)
		{
			// Copy-construct
			Allocator<TYPE>::CopyConstruct(ptr, this->ptr, capacity);
		}
		else
		{
			// Copy-construct
			Allocator<TYPE>::CopyConstruct(ptr, this->ptr, this->capacity);

			// Construct
			memset(ptr + this->capacity, 0, sizeof(TYPE) * (capacity - this->capacity));
			Allocator<TYPE>::Construct(ptr + this->capacity, capacity - this->capacity);
		}

		// Delete
		if (this->ptr != NULL)
		{
			Allocator<TYPE>::Destroy(this->ptr, this->capacity);
			Allocator<TYPE>::Free(this->ptr);
		}

		// Store
		this->ptr = ptr;
		this->capacity = capacity;
	}

	template <class TYPE>
	void Container<TYPE>::Reserve(int capacity)
	{
		if (capacity > this->capacity)
			this->Reallocate(capacity);
	}

	template <class TYPE>
	void Container<TYPE>::Grow(int index)
	{
		// Double capacity
		int capacity = Max(this->capacity << 1, 8);

		// Check if capacity is sufficient to accomodate index
		if (capacity <= index)
			capacity = index + 1;

		// Grow
		this->Reallocate(capacity);
	}

	template <class TYPE>
	void Container<TYPE>::Free()
	{
		if (this->ptr != NULL)
		{
			// Delete
			Allocator<TYPE>::Destroy(this->ptr, this->capacity);
			Allocator<TYPE>::Free(this->ptr);

			// Initialize
			this->ptr = NULL;
			this->capacity = 0;
		}
	}

	template <class TYPE>
	const Container<TYPE> & Container<TYPE>::operator =(const Container<TYPE> & src)
	{
		if (this != &src)
		{
			// Free
			this->Free();
			
			// Allocate
			TYPE * ptr = Allocator<TYPE>::Allocate(src.capacity);

			// Copy-construct
			Allocator<TYPE>::CopyConstruct(ptr, src.ptr, src.capacity);

			// Store
			this->ptr = ptr;
			this->capacity = src.capacity;
		}
		return * this;
	}
}
