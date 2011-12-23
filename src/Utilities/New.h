#pragma once
#include <stdlib.h>

namespace Utilities
{
	class BLTag{};
	const BLTag bl = BLTag();
}

// Global operator new and delete
void * operator new(size_t size, const Utilities::BLTag &);
void operator delete(void * ptr, const Utilities::BLTag &);
void * operator new [](size_t size, const Utilities::BLTag &);
void operator delete [] (void * ptr, const Utilities::BLTag &);
