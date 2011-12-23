#pragma once

#include <memory.h>

namespace Utilities
{
	// WeakString - need not to be 0 terminated
	template <class TYPE>
	class WeakString
	{
	private:
		// Fields
		TYPE * ptr;
		int length;

	public:
		// Construction
		WeakString(TYPE * ptr, int length);

		// Operations
		bool operator ==(const char * ptr) const;
	};

	// Construction is defined in C++ file to allow only selected types

	// Operations
	template <class TYPE> inline
	bool WeakString<TYPE>::operator ==(const char * ptr) const
	{
		return memcmp(this->ptr, ptr, this->length) == 0;
	}
}
