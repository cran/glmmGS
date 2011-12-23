#include "Buffer.h"
#include "Exceptions/Exceptions.h"
#include <string.h>
#include <memory.h>

namespace Utilities
{
	// Construction
	Buffer::Buffer(int capacity)
		: Container<char>(capacity), length(0)
	{
	}

	// Appending
	void Buffer::Append(const char * msg)
	{
		int msg_len = static_cast<int>(strlen(msg));
		int max_len = Min(this->capacity - 1 - this->length, msg_len);
		if (max_len > 0)
		{
			memcpy(this->ptr + this->length, msg, max_len);
			this->length += max_len;
		}
	}

	void Buffer::Empty()
	{
		memset(this->ptr, 0, this->capacity);
		this->length = 0;
	}
}
