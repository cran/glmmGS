#pragma once

#include "New.h"
#include <new>

namespace Utilities
{
	// Allocator
	template <class TYPE>
	class Allocator
	{
	public:
		static TYPE * Allocate(int size);
		static void Free(TYPE * ptr);
		static void Construct(TYPE * ptr, int size);
		static void CopyConstruct(TYPE * dst, const TYPE * src, int size);
		static void Destroy(TYPE * ptr, int size);
	};

	// Allocator
	template <class TYPE> inline
	TYPE * Allocator<TYPE>::Allocate(int size)
	{
		return (size > 0) ? static_cast<TYPE *>(::operator new [](size * sizeof(TYPE), bl)) : NULL;
	}

	template <class TYPE> inline
	void Allocator<TYPE>::Free(TYPE * ptr)
	{
		::operator delete [](ptr);
	}

	template <class TYPE>
	void Allocator<TYPE>::Construct(TYPE * ptr, int size)
	{
		int i = 0;
		try
		{
			for (; i < size; ++i, ++ptr)
				::new(ptr) TYPE;
		}
		catch (...)
		{
			for (--ptr; i > 0; --i, --ptr)
				ptr->~TYPE();
			throw;
		};
	}

	template <class TYPE>
	void Allocator<TYPE>::CopyConstruct(TYPE * dst, const TYPE * src, int size)
	{
		int i = 0;
		try
		{
			for (; i < size; ++i, ++dst, ++src)
				::new(dst) TYPE(*src);
		}
		catch (...)
		{
			for (--dst; i > 0; --i, --dst)
				dst->~TYPE();
			throw;
		};
	}
	
	template <class TYPE> inline
	void Allocator<TYPE>::Destroy(TYPE * ptr, int size)
	{
		for (ptr += size - 1; size > 0; --size, --ptr)
			ptr->~TYPE();
	}	
}
