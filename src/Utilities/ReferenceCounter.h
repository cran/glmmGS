#ifndef UTILITIES_REFERENCECOUNTER_H
#define UTILITIES_REFERENCECOUNTER_H

#include "New.h"
#include <stdlib.h>

namespace Utilities
{
	// ReferenceCounter
	class ReferenceCounter
	{
	private:
		// Disable assignment
		const ReferenceCounter & operator =(const ReferenceCounter &);

		// Fields
		int * counter;

	public:
		// Attributes
		int Count() const;

		// Construction
		ReferenceCounter();
		explicit ReferenceCounter(void * ptr);
		ReferenceCounter(const ReferenceCounter & refCounter); // Add reference
		
		// Methods
		void Reset(void * ptr);
		void AddReference(const ReferenceCounter & refCounter);
		int RemoveReference();
	};

	// Definition
	inline
	int ReferenceCounter::Count() const
	{
		return this->counter ? *this->counter : 0;
	}
	
	inline
	ReferenceCounter::ReferenceCounter()
		: counter(NULL)
	{
	}

	inline
	ReferenceCounter::ReferenceCounter(void * ptr)
		: counter(ptr != NULL ? new(bl) int(1) : NULL)
	{
	}

	inline
	ReferenceCounter::ReferenceCounter(const ReferenceCounter & refCounter)
		: counter(refCounter.counter)
	{
		if (this->counter != NULL)
			++(*this->counter);
	}
}

#endif
