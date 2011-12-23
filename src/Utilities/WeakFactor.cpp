#include "Exceptions/Exception.h"
#include "Vector.h"
#include "WeakFactor.h"
#include "IO/BasicPrint.h"

namespace Utilities
{
	WeakFactor::WeakFactor(const int * levels, int size)
		: levels(NULL), size(0), nlevels(0)
	{
		if (size > 0)
		{
			// Evaluate min and max levels
			int max_level = levels[0];
			int min_level = levels[0];
			for (int i = 1; i < size; ++i)
			{
				if (levels[i] > max_level)
					max_level = levels[i];
				if (levels[i] < min_level)
					min_level = levels[i];
			}

			// Check min_level
			if (min_level != 0)
				throw Exceptions::Exception("Levels must be zero-based indices");

			// Check that levels are complete
			const int nlevels = max_level + 1;
			Vector<int> count(nlevels);
			for (int i = 0; i < size; ++i)
				++count(levels[i]);
			for (int l = 0; l < nlevels; ++l)
				if (count(l) == 0)
					throw Exceptions::Exception("Incomplete levels");

			// Set member variables
			this->levels = levels;
			this->size = size;
			this->nlevels = max_level + 1;
		}
	}
}
