#pragma once
#include <memory.h>

namespace Utilities
{
	// Swap
	template <class TYPE>
	void Swap(TYPE & a, TYPE & b)
	{
		struct Bytes 
		{
			unsigned char x[sizeof(TYPE)];
		};

		Bytes * aptr = reinterpret_cast<Bytes *>(&a);
		Bytes * bptr = reinterpret_cast<Bytes *>(&b);
		Bytes tmp = *aptr;
		*aptr = *bptr;
		*bptr = tmp;
	}

	// Move
	template <class TYPE>
	void Move(TYPE & a, TYPE & b)
	{
		struct Bytes 
		{
			unsigned char x[sizeof(TYPE)];
		};

		Bytes * aptr = reinterpret_cast<Bytes *>(&a);
		Bytes * bptr = reinterpret_cast<Bytes *>(&b);
		*aptr = *bptr;
		memset(reinterpret_cast<void *>(bptr), 0, sizeof(TYPE));
	}

	// Min
	template <class TYPE> inline
	const TYPE & Min(const TYPE &  a, const TYPE & b)
	{
		return a < b ? a : b;
	}

	// Max
	template <class TYPE> inline
	const TYPE & Max(const TYPE &  a, const TYPE & b)
	{
		return a > b ? a : b;
	}
}
