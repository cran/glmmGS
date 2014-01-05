#ifndef UTILITIES_EXCEPTIONS_EXCEPTION_H
#define UTILITIES_EXCEPTIONS_EXCEPTION_H

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

#endif
