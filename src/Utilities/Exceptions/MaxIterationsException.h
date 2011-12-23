#pragma once

#include "NumericException.h"

namespace Utilities
{
	namespace Exceptions
	{
		class MaxIterationsException : public NumericException
		{
		public:
			MaxIterationsException(const char * message = "Exceeded maximum number of iterations") : NumericException(message)
			{
			}
		};
	}
}
