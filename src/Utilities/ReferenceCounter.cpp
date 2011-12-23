#include "ReferenceCounter.h"
#include "Exceptions/Assertions.h"

namespace Utilities
{
	void ReferenceCounter::Reset(void * ptr)
	{
		// This method should be called only after RemoveReference
		_ASSERT_ARGUMENT(this->counter == NULL);
		if (ptr != NULL)
			this->counter = new(bl) int(1);
	}

	void ReferenceCounter::AddReference(const ReferenceCounter & refCounter)
	{
		// This method should only be called after RemoveReference
		_ASSERT_ARGUMENT(this->counter == NULL);
		if (refCounter.counter)
		{
			this->counter = refCounter.counter;
			++(*this->counter);
		}
	}
	
	int ReferenceCounter::RemoveReference()
	{
		if (this->counter != NULL)
		{
			const int count = --(*this->counter);
			if (count == 0)
				delete this->counter;
			this->counter = NULL;
			return count;
		}
		else
		{
			return -1;
		}
	}
}
