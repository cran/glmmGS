#pragma once

namespace Utilities
{
	namespace Exceptions
	{
		// Exception
		class Exception
		{
		private:
			const char * message;

		public:
			Exception(const char * message = "Exception");
			const char * Message() const;
		};

		// Definition
		inline
		const char * Exception::Message() const
		{
			return this->message;
		}
	}
}
