#pragma once

#include "NumericException.h"

namespace Utilities
{
	namespace Exceptions
	{
		class IntegerOverflowException : public NumericException
		{
		public:
			IntegerOverflowException(const char * message = "Integer overflow") : NumericException(message)
			{
			}
		};
	}
}
