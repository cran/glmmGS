#include "../Utilities.h"
#include "../Math/Math.h"
#include "VectorFunctions.h"

namespace Utilities 
{
	namespace LinearAlgebra
	{
		// Operators
		Vector<double> & operator *=(Vector<double> & v, double a)
		{
			int n = v.Size();
			for (int i = 0; i < n; ++i)
				v(i) *= a;
			return v;
		}

		Vector<double> & operator +=(Vector<double> & v, const Vector<double> & w)
		{
			_ASSERT_ARGUMENT(v.Size() == w.Size())
			int n = v.Size();
			for (int i = 0; i < n; ++i)
				v(i) += w(i);
			return v;
		}

		Vector<double> & operator -=(Vector<double> & v, const Vector<double> & w)
		{
			_ASSERT_ARGUMENT(v.Size() == w.Size())
			int n = v.Size();
			for (int i = 0; i < n; ++i)
				v(i) -= w(i);
			return v;
		}

		Vector<double> operator *(double a, const Vector<double> & v)
		{
			int n = v.Size();
			Vector<double> y(n);
			for (int i = 0; i < n; ++i)
				y(i) = a * v(i);
			return y;
		}

		Vector<double> operator +(const Vector<double> & v, const Vector<double> & w)
		{
			_ASSERT_ARGUMENT(v.Size() == w.Size())
			int n = v.Size();
			Vector<double> y(n);
			for (int i = 0; i < n; ++i)
				y(i) = v(i) + w(i);
			return y;
		}

		Vector<double> operator -(const Vector<double> & v, const Vector<double> & w)
		{
			_ASSERT_ARGUMENT(v.Size() == w.Size())
			int n = v.Size();
			Vector<double> y(n);
			for (int i = 0; i < n; ++i)
				y(i) = v(i) - w(i);
			return y;
		}

		// Functions
		double Sum(const Vector<double> & v)
		{
			const int n = v.Size();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += v(i);
			return sum;
		}

		double ScalarProduct(const Vector<double> & v, const Vector<double> & w)
		{
			_ASSERT_ARGUMENT(v.Size() == w.Size())
			const int n = v.Size();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += v(i) * w(i);
			return sum;
		}

		double Square(const Vector<double> & v)
		{
			const int n = v.Size();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += Math::Square(v(i));
			return sum;
		}
		
		// Max-Min Abs implementation
		double MaxAbsImpl(double x)
		{
			return fabs(x);
		}

		double MinAbsImpl(double x)
		{
			return fabs(x);
		}

		template <class TYPE>
		double MaxAbsImpl(const Vector<TYPE> & v)
		{
			const int n = v.Size();
			_VALIDATE_ARGUMENT(n > 0);
			double max = MaxAbsImpl(v(0));
			for (int i = 1; i < n; ++i)
			{
				const double a = MaxAbsImpl(v(i));
				if (a > max)
					max = a;
			}
			return max;
		}

		template <class TYPE>
		double MinAbsImpl(const Vector<TYPE> & v)
		{
			const int n = v.Size();
			_VALIDATE_ARGUMENT(n > 0);
			double min = MinAbsImpl(v(0));
			for (int i = 1; i < n; ++i)
			{
				const double a = MinAbsImpl(v(i));
				if (a < min)
					min = a;
			}
			return min;
		}

		// Min-Max Abs
		double MaxAbs(const Vector<double> & v)
		{
			return MaxAbsImpl(v);
		}

		double MinAbs(const Vector<double> & v)
		{
			return MinAbsImpl(v);
		}

		// Vectorial functions
		int TotalSize(const Vector<Vector<double> > & x)
		{
			const int n = x.Size();
			int size = 0;
			for (int i = 0; i < n; ++i)
				size += x(i).Size();
			return size;
		}

		double ScalarProduct(const Vector<Vector<double> > & x, const Vector<Vector<double> > & y)
		{
			_ASSERT_ARGUMENT(x.Size() == y.Size());
			const int n = x.Size();
			double sum = 0;
			for (int i = 0; i < n; ++i)
				sum += ScalarProduct(x(i), y(i));
			return sum;
		}

		// Min-Max Abs
		double MaxAbs(const Vector<Vector<double> > & v)
		{
			return MaxAbsImpl(v);
		}

		double MinAbs(const Vector<Vector<double> > & v)
		{
			return MinAbsImpl(v);
		}
	}
}
