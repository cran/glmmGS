#ifndef UTILITIES_POINTER_H
#define UTILITIES_POINTER_H

#include "ReferenceCounter.h"

namespace Utilities
{
	// Pointer
	template <class TYPE>
	class Pointer : public ReferenceCounter
	{
	private:
		// Friend class
		template <class OTHER> friend class Pointer;
		
		// Fields
		TYPE * ptr;

	public:
		// Default constructor
		Pointer();

		// Copy constructor
		Pointer(const Pointer & src);
		template <class OTHER> Pointer(const Pointer<OTHER> & src);

		// Raw pointer constructor
		template <class OTHER> explicit Pointer(OTHER * ptr);

		// Destructor
		~Pointer();

		// Attributes
		bool IsNull() const;

		// Reset to NULL, free memory if necessary
		void Reset();
		
		// Reset to ptr, free memory if necessary
		template <class OTHER> void Reset(OTHER * ptr);

		// Assignment
		const Pointer & operator =(const Pointer & src);
		template <class OTHER> const Pointer & operator =(const Pointer<OTHER> & src);

		// Indirection
		TYPE & operator *();
		const TYPE & operator *() const;
		TYPE * operator ->();
		const TYPE * operator ->() const;
	};

	// Definition
	template <class TYPE> inline
	Pointer<TYPE>::Pointer()
		: ptr(NULL)
	{
	}

	template <class TYPE> inline
	Pointer<TYPE>::Pointer(const Pointer<TYPE> & src)
		: ReferenceCounter(src), ptr(src.ptr)
	{
	}
		
	template <class TYPE>
	template <class OTHER> inline
	Pointer<TYPE>::Pointer(const Pointer<OTHER> & src)
		: ReferenceCounter(src), ptr(src.ptr)
	{
	}

	template <class TYPE>
	template <class OTHER> inline
	Pointer<TYPE>::Pointer(OTHER * ptr)
		: ReferenceCounter(ptr), ptr(ptr)
	{
	}

	template <class TYPE> inline
	Pointer<TYPE>::~Pointer()
	{
		if (ReferenceCounter::RemoveReference() == 0)
			delete this->ptr;
	}

	template <class TYPE> inline
	bool Pointer<TYPE>::IsNull() const
	{
		return this->ptr == NULL;
	}
	
	template <class TYPE>
	void Pointer<TYPE>::Reset()
	{
		if (ReferenceCounter::RemoveReference() == 0)
			delete this->ptr;
		this->ptr = NULL;
	}

	template <class TYPE>
	template <class OTHER>
	void Pointer<TYPE>::Reset(OTHER * ptr)
	{
		if (ReferenceCounter::RemoveReference() == 0)
			delete this->ptr;
		this->ptr = ptr;
		ReferenceCounter::Reset(ptr);
	}

	template <class TYPE>
	const Pointer<TYPE> & Pointer<TYPE>::operator =(const Pointer<TYPE> & src)
	{
		if (this->ptr != src.ptr)
		{
			if (ReferenceCounter::RemoveReference() == 0)
				delete this->ptr;
			this->ptr = src.ptr;
			ReferenceCounter::AddReference(src);
		}
		return *this;
	}
		
	template <class TYPE>
	template <class OTHER>
	const Pointer<TYPE> & Pointer<TYPE>::operator =(const Pointer<OTHER> & src)
	{
		if (this->ptr != src.ptr)
		{
			if (ReferenceCounter::RemoveReference() == 0)
				delete this->ptr;
			this->ptr = src.ptr;
			ReferenceCounter::AddReference(src);
		}
		return *this;
	}

	template <class TYPE> inline
	TYPE & Pointer<TYPE>::operator *()
	{
		return *this->ptr;
	}

	template <class TYPE> inline
	const TYPE & Pointer<TYPE>::operator *() const
	{
		return *this->ptr;
	}
	
	template <class TYPE> inline
	TYPE * Pointer<TYPE>::operator ->()
	{
		return this->ptr;
	}

	template <class TYPE> inline
	const TYPE * Pointer<TYPE>::operator ->() const
	{
		return this->ptr;
	}
}

#endif
