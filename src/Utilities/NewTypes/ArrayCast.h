#ifndef UTILITIES_NEWTYPES_ARRAYCAST_H
#define UTILITIES_NEWTYPES_ARRAYCAST_H

#include "Cast.h"
#include "Array.h"
#include "Vector.h"

namespace Utilities
{
	namespace NewTypes
	{
		// Cast class
		template <class TYPE>
		class Cast<Array<TYPE> > : public Array<TYPE>
		{
			typedef Array<TYPE> To;

		public:
			// Cast vector
			Cast(Vector<TYPE> & src)
					: To(src.ptr, src.counter, src.size)
			{
			}
		};

		// Const cast class
		template <class TYPE>
		class Cast<const Array<TYPE> > : public Array<TYPE>
		{
			typedef const Array<TYPE> To;

		public:
			// Cast vector
			Cast(const Vector<TYPE> & src)
					: To(src.ptr, src.counter, src.size)
			{
			}
		};
	}
}

#endif
