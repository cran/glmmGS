#ifndef UTILITIES_NEWTYPES_EXTERNAL_H
#define UTILITIES_NEWTYPES_EXTERNAL_H

namespace Utilities
{
	namespace NewTypes
	{
		template <class TYPE>
		class External
		{
		private:
			TYPE * ptr;
		public:
			External(TYPE * ptr) : ptr(ptr) {}
			operator TYPE *() {return this->ptr;}
		};
	}
}

#endif
