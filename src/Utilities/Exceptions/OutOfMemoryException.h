#pragma once

#include "Exception.h"

namespace Utilities
{
	namespace Exceptions
	{
		class OutOfMemoryException : public Exception
		{
		public:
			OutOfMemoryException(const char * message = "Out of memory") : Exception(message)
			{
			}
		};
	}
}
