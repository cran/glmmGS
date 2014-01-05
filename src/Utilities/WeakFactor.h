#ifndef UTILITIES_WEAKFACTOR_H
#define UTILITIES_WEAKFACTOR_H

#include "Exceptions/Assertions.h"

namespace Utilities
{
	// WeakFactor
	class WeakFactor
	{
	private:
		// Fields
		const int * levels;
		int size;
		int nlevels;

	public:
		// Construction
		WeakFactor(const int * levels, int size);

		// Properties
		int NumberOfLevels() const;
		int Level(int obs) const;
		int Size() const;
	};

	// Definition
	inline
	int WeakFactor::Size() const
	{
		return this->size;
	}

	inline
	int WeakFactor::NumberOfLevels() const
	{
		return this->nlevels;
	}

	inline
	int WeakFactor::Level(int obs) const
	{
		_ASSERT_ARGUMENT(0 <= obs && obs < this->size);
		return this->levels[obs];
	}
}

#endif
