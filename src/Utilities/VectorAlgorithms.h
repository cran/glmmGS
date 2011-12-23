#pragma once

#include "Algorithms.h"
#include "Vector.h"
#include "Exceptions/Assertions.h"

namespace Utilities
{
	// Vector min
	template <class TYPE>
	TYPE Min(const Vector<TYPE> & v)
	{
		_VALIDATE_ARGUMENT(v.Size() > 0);
		const int n = v.Size();
		TYPE min = v(0);
		for (int i = 1; i < n; ++i)
			if (min > v(i))
				min = v(i);
		return min;
	}
		
	// Vector max
	template <class TYPE>
	TYPE Max(const Vector<TYPE> & v)
	{
		_VALIDATE_ARGUMENT(v.Size() > 0);
		const int n = v.Size();
		TYPE max = v(0);
		for (int i = 1; i < n; ++i)
			if (max < v(i))
				max = v(i);
		return max;
	}

	// Vectorial max - TODO: test this
	template <class TYPE>
	TYPE Max(const Vector<Vector<TYPE> > & v)
	{
		_VALIDATE_ARGUMENT(v.Size() > 0);
		const int n = v.Size();
		TYPE max = Max(v(0));
		for (int i = 1; i < n; ++i)
			max = Max(max, Max(v(i)));
		return max;
	}

	// IsSorted
	template <class TYPE>
	bool IsSorted(const Vector<TYPE> & v)
	{
		const int n = v.Size();
		for (int i = 1; i < n; ++i)
			if (!(v(i - 1) <= v(i)))
				return false;
		return true;
	}
}
