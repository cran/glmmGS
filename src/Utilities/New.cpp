#include "New.h"
#include "Exceptions/OutOfMemoryException.h"
#include <new>

// Global operator new and delete
void * operator new(size_t size, const Utilities::BLTag &)
{
	void * ptr = ::operator new(size, std::nothrow);
	if (ptr == NULL)
		throw Utilities::Exceptions::OutOfMemoryException();
	return ptr;
}

void operator delete(void * ptr, const Utilities::BLTag &)
{
	::operator delete(ptr);
}

void * operator new [](size_t size, const Utilities::BLTag &)
{
	void * ptr = ::operator new [](size, std::nothrow);
	if (ptr == NULL)
		throw Utilities::Exceptions::OutOfMemoryException();
	return ptr;
}

void operator delete [] (void * ptr, const Utilities::BLTag &)
{
	::operator delete [](ptr);
}
