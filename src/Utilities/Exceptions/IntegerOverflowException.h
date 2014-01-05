#ifndef UTILITIES_EXCEPTIONS_INTEGEROVERFLOWEXCEPTION_H
#define UTILITIES_EXCEPTIONS_INTEGEROVERFLOWEXCEPTION_H

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

#endif
