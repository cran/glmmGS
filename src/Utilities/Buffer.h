#pragma once

#include "Container.h"

namespace Utilities
{
	// Buffer
	class Buffer : public Container<char>
	{
	private:
		// Fields
		int length;

	public:
		// Construction
		Buffer(int capacity);

		// Properties
		const char * Pointer() const;
		int Length() const;

		// Operations
		void Append(const char * msg);
		void Empty();
	};

	// Definition
	inline
	const char * Buffer::Pointer() const
	{
		return this->ptr;
	}

	inline
	int Buffer::Length() const
	{
		return this->length;
	}
}
