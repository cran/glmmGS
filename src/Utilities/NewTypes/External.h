#pragma once

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
