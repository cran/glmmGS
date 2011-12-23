#pragma once

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
