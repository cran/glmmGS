#ifndef UTILITIES_EXCEPTIONS_INVALIDOPERATIONEXCEPTION_H
#define UTILITIES_EXCEPTIONS_INVALIDOPERATIONEXCEPTION_H

#include "Exception.h"

namespace Utilities
{
	namespace Exceptions
	{
		// InvalidOperationException
		class InvalidOperationException : public Exception
		{
		public:
			InvalidOperationException(const char * message = "Invalid operation") : Exception(message)
			{
			}
		};
	}
}

#endif
