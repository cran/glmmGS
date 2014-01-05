#ifndef UTILITIES_EXCEPTIONS_NUMERICEXCEPTION_H
#define UTILITIES_EXCEPTIONS_NUMERICEXCEPTION_H

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

#endif
