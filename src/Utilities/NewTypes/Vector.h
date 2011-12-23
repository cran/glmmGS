#pragma once

#include "../Exceptions/Assertions.h"
#include "../New.h"
#include "../ReferenceCounter.h"
#include "External.h"

namespace Utilities
{
	namespace NewTypes
	{
		// Vector
		template <class TYPE>
		class Vector
		{
			template <class OTHER> friend class Cast;

		private:
			// Fields
			TYPE * ptr;
			ReferenceCounter counter;
			int size;

		public:
			// Construction
			Vector();						// Default
			explicit Vector(int size);		// Size
			Vector(TYPE * ptr, const ReferenceCounter & counter, int size); // From another ref-counted pointer
			Vector(External<TYPE> ptr, int size); // From an external pointer
			~Vector();

			// Properties
			int Size() const;

			// Assignment
			const Vector<TYPE> & operator =(const Vector<TYPE> & src);

			// Element access
			TYPE & operator ()(int i);
			const TYPE & operator ()(int i) const;
		};


		// Definition

		// Construction
		template <class TYPE> inline
		Vector<TYPE>::Vector()
			: ptr(NULL), size(0)
		{
		}

		template <class TYPE> inline
		Vector<TYPE>::Vector(int size)
			: ptr(new(bl) TYPE[size]), counter(ptr), size(size)
		{
		}

		template <class TYPE> inline
		Vector<TYPE>::Vector(TYPE * ptr, const ReferenceCounter & counter, int size)
			: ptr(ptr), counter(counter), size(size)
		{
		}

		template <class TYPE> inline
		Vector<TYPE>::Vector(External<TYPE> ptr, int size)
			: ptr(ptr), counter(NULL), size(size)
		{
		}

		template <class TYPE> inline
		Vector<TYPE>::~Vector()
		{
			if (this->counter.RemoveReference() == 0)
				delete [] this->ptr;
		}

		// Properties
		template <class TYPE> inline
		int Vector<TYPE>::Size() const
		{
			return this->size;
		}

		// Assignment
		template <class TYPE>
		const Vector<TYPE> & Vector<TYPE>::operator =(const Vector<TYPE> & src)
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
		TYPE & Vector<TYPE>::operator ()(int i)
		{
			_ASSERT_ARGUMENT(i >= 0 && i < this->size);
			return this->ptr[i];
		}

		template <class TYPE> inline
		const TYPE & Vector<TYPE>::operator ()(int i) const
		{
			_ASSERT_ARGUMENT(i >= 0 && i < this->size);
			return this->ptr[i];
		}
	}
}
