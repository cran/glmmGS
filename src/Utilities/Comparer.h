#pragma once

#include "Vector.h"

namespace Utilities
{
	// Comparer
	class Comparer
	{
		// Fields
		double relative_tolerance;
		double absolute_tolerance;

	public:
		// Construction
		Comparer(double relative_tolerance, double absolute_tolerance);

		// Methods
		bool AreEqual(double x, double y) const;
		bool IsZero(double eps, double x) const;

		template <class TYPE> bool AreEqual(const Vector<TYPE> & x, const Vector<TYPE> & y) const;
		template <class TYPE> bool IsZero(const Vector<TYPE> & eps, const Vector<TYPE> & x) const;
	};


	template <class TYPE>
	bool Comparer::AreEqual(const Vector<TYPE> & x, const Vector<TYPE> & y) const
	{
		_VALIDATE_ARGUMENT(x.Size() == y.Size());
		const int n = x.Size();
		for (int i = 0; i < n; ++i)
			if (!Comparer::AreEqual(x(i), y(i)))
				return false;
		return true;
	}

	template <class TYPE>
	bool Comparer::IsZero(const Vector<TYPE> & eps, const Vector<TYPE> & x) const
	{
		_ASSERT_ARGUMENT(eps.Size() == x.Size())
		const int n = x.Size();
		for (int i = 0; i < n; ++i)
			if (Comparer::IsZero(eps(i), x(i)) == false)
				return false;
		return true;
	}

}
