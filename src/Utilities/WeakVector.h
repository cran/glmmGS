#pragma once

#include "Exceptions/Exception.h"
#include "Exceptions/Assertions.h"
#include "IO/BasicPrint.h"

namespace Utilities
{
	// WeakVector
	template <class TYPE>
	class WeakVector
	{
	private:
		TYPE * ptr;
		int size;

	public:
		// Construction
		WeakVector(TYPE * ptr, int size);

		// Properties
		int Size() const;

		// Element access
		TYPE & operator ()(int i);
		const TYPE & operator ()(int i) const;
	};

	// Definition

	// WeakVector - Construction
	template <class TYPE>
	WeakVector<TYPE>::WeakVector(TYPE * ptr, int size)
		: ptr(NULL), size(0)
	{
		if (ptr != NULL && size > 0)
		{
			this->ptr = ptr;
			this->size = size;
		}
		else
			throw Exceptions::Exception("Invalid weak vector");
	}

	// Properties
	template <class TYPE> inline
	int WeakVector<TYPE>::Size() const
	{
		return this->size;
	}

	// Element access
	template <class TYPE> inline
	TYPE & WeakVector<TYPE>::operator ()(int i)
	{
		_ASSERT_ARGUMENT(0 <= i && i < this->size);
		return this->ptr[i];
	}

	template <class TYPE> inline
	const TYPE & WeakVector<TYPE>::operator ()(int i) const
	{
		_ASSERT_ARGUMENT(0 <= i && i < this->size);
		return this->ptr[i];
	}
}
