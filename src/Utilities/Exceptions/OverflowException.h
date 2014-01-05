#ifndef UTILITIES_EXCEPTIONS_OVERFLOWEXCEPTION_H
#define UTILITIES_EXCEPTIONS_OVERFLOWEXCEPTION_H

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

#endif
