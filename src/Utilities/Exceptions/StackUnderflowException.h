#ifndef UTILITIES_EXCEPTIONS_STACKUNDERFLOWEXCEPTION_H
#define UTILITIES_EXCEPTIONS_STACKUNDERFLOWEXCEPTION_H

#include "Exception.h"

namespace Utilities
{
	namespace Exceptions
	{
		class StackUnderflowException : public Exception
		{
		public:
			StackUnderflowException(const char * message = "Stack underflow") : Exception(message)
			{
			}
		};
	}
}

#endif
