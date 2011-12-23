#pragma once

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
