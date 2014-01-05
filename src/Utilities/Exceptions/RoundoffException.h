#ifndef UTILITIES_EXCEPTIONS_ROUNDOFFEXCEPTION_H
#define UTILITIES_EXCEPTIONS_ROUNDOFFEXCEPTION_H

#include "NumericException.h"

namespace Utilities
{
	namespace Exceptions
	{
		class RoundoffException : public NumericException
		{
		public:
			RoundoffException(const char * message = "Round-off exception") : NumericException(message)
			{
			}
		};
	}
}

#endif
