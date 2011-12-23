#include <stdlib.h>
#include "Exceptions/Exception.h"
#include "WeakString.h"

namespace Utilities
{
	// WeakString - construction
	template <class TYPE>
	WeakString<TYPE>::WeakString(TYPE * ptr, int length)
		: ptr(NULL), length(0)
	{
		if (ptr != NULL && length > 0)
		{
			this->ptr = ptr;
			this->length = length;
		}
		else
			throw Exceptions::Exception("Invalid weak string");
	}

	// Explicit instantiation
	template class WeakString<const char>;
}
