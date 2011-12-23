#pragma once

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
