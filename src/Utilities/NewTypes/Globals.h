#include "../Exceptions/Assertions.h"
#include "Vector.h"

namespace Utilities
{
	namespace NewTypes
	{
		// Copy vector
		template <class DST_VECTOR, class SRC_VECTOR>
		void Copy(DST_VECTOR & dst,	const SRC_VECTOR & src)
		{
			_ASSERT_ARGUMENT(dst.Size() == src.Size());
			for (int i = 0; i < dst.Size(); ++i)
				dst(i) = src(i);
		}

		// Vector assignment to a constant
		template <class DST_VECTOR, class TYPE>
		void Set(DST_VECTOR & dst, const TYPE & x)
		{
			const int n = dst.Size();
			for (int i = 0; i < n; ++i)
				dst(i) = x;
		}
	}
}
