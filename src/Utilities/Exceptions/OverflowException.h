#pragma once

#include "NumericException.h"

namespace Utilities
{
	namespace Exceptions
	{
		class OverflowException : public NumericException
		{
		public:
			OverflowException(const char * message = "Overflow") : NumericException(message)
			{
			}
		};
	}
}
