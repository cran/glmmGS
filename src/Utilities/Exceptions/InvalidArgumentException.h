#ifndef UTILITIES_EXCEPTIONS_INVALIDARGUMENTEXCEPTION_H
#define UTILITIES_EXCEPTIONS_INVALIDARGUMENTEXCEPTION_H

#include "Exception.h"

namespace Utilities
{
	namespace Exceptions
	{
		// InvalidArgumentException
		class InvalidArgumentException : public Exception
		{
		public:
			InvalidArgumentException(const char * message = "Invalid argument") : Exception(message)
			{
			}
		};
	}
}

#endif
