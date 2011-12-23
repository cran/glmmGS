#pragma once

#include <stdio.h>
#include "Stream.h"

namespace Utilities
{
	namespace IO
	{
		// Basic print functions
		void Print(const char * format);
		template <class TYPE> void Print(const char * format, TYPE value);

		// Definition
		inline
		void Print(const char * format)
		{
			fprintf(stream, format);
			fflush(stream);
		}

		template <class TYPE>
		void Print(const char * format, TYPE value)
		{
			fprintf(stream, format, value);
			fflush(stream);
		}
	}
}
