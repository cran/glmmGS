#pragma once

#include "../Exceptions/Assertions.h"
#include "../New.h"
#include "../ReferenceCounter.h"
#include "External.h"

namespace Utilities
{
	namespace NewTypes
	{
		// Array
		template <class TYPE>
		class Array
		{
		private:
			// Fields
			TYPE * ptr;
			ReferenceCounter counter;
			int size;

		public:
			// Construction
			Array();						// Default
			explicit Array(int size);		// Size
			Array(TYPE * ptr, const ReferenceCounter & counter, int size); // From another ref-counted pointer
			Array(External<TYPE> ptr, int size); // From an external pointer
			~Array();

			// Cast
			operator bool() const;

			// Pointer access - if possible should be avoided
			TYPE * pointer();
			const TYPE * pointer() const;

			// Assignment
			const Array<TYPE> & operator =(const Array<TYPE> & src);

			// Element access
			TYPE & operator [](int i);
			const TYPE & operator [](int i) const;
		};


		// Definition

		// Construction
		template <class TYPE> inline
		Array<TYPE>::Array()
			: ptr(NULL), size(0)
		{
		}

		template <class TYPE> inline
		Array<TYPE>::Array(int size)
			: ptr(new(bl) TYPE[size]), counter(ptr), size(size)
		{
		}

		template <class TYPE> inline
		Array<TYPE>::Array(TYPE * ptr, const ReferenceCounter & counter, int size)
			: ptr(ptr), counter(counter), size(size)
		{
		}

		template <class TYPE> inline
		Array<TYPE>::Array(External<TYPE> ptr, int size)
			: ptr(ptr), counter(NULL), size(size)
		{
		}

		template <class TYPE> inline
		Array<TYPE>::~Array()
		{
			if (this->counter.RemoveReference() == 0)
				delete [] this->ptr;
		}

		// Cast
		template <class TYPE> inline
		Array<TYPE>::operator bool () const
		{
			return (this->ptr != NULL);
		}

		template <class TYPE> inline
		TYPE * Array<TYPE>::pointer()
		{
			return this->ptr;
		}

		template <class TYPE> inline
		const TYPE * Array<TYPE>::pointer() const
		{
			return this->ptr;
		}

		// Assignment
		template <class TYPE>
		const Array<TYPE> & Array<TYPE>::operator =(const Array<TYPE> & src)
		{
			if (this->ptr != src.ptr)
			{
				if (this->counter.RemoveReference() == 0)
					delete [] this->ptr;
				this->ptr = src.ptr;
				this->size = src.size;
				this->counter.AddReference(src.counter);
			}
			return *this;
		}

		// Element access
		template <class TYPE> inline
		TYPE & Array<TYPE>::operator [](int i)
		{
			_ASSERT_ARGUMENT(i >= 0 && i < this->size);
			return this->ptr[i];
		}

		template <class TYPE> inline
		const TYPE & Array<TYPE>::operator [](int i) const
		{
			_ASSERT_ARGUMENT(i >= 0 && i < this->size);
			return this->ptr[i];
		}
	}
}
