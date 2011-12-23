#pragma once

#include "Exception.h"

namespace Utilities
{
	namespace Exceptions
	{
		class NumericException : public Exception
		{
		public:
			NumericException(const char * message = "Numeric exception") : Exception(message)
			{
			}
		};
	}
}
