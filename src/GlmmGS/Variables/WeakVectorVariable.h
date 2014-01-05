#ifndef GLMMGS_UTILITIES_VARIABLES_WEAKVECTORVARIABLE_H
#define GLMMGS_UTILITIES_VARIABLES_WEAKVECTORVARIABLE_H

#include "../Standard.h"
#include "IVariable.h"

namespace GlmmGS
{
	namespace Variables
	{
		// WeakVectorVariable
		template <class TYPE>
		class WeakVectorVariable : public IVariable
		{
		private:
			// Fields
			WeakVector<TYPE> values;

			// Operations
			void UpdatePredictor(Vector<double> & eta, double beta) const;
			double ScalarProduct(const Vector<double> & values) const;
			double ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable) const;
			double ScalarProduct(const Vector<double> & weights, WeakVector<const int> values) const;
			double ScalarProduct(const Vector<double> & weights, WeakVector<const double> values) const;
			template <class OTHER> double ScalarProductImpl(const Vector<double> & weights, WeakVector<const OTHER> values) const;

			// Stratified Operations
			void UpdatePredictor(Vector<double> & eta, const Vector<double> & beta, WeakFactor factor) const;
			Vector<double> ScalarProduct(const Vector<double> & values, WeakFactor factor) const;
			Vector<double> ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable, WeakFactor factor) const;
			Vector<double> ScalarProduct(const Vector<double> & weights, WeakVector<const int> values, WeakFactor factor) const;
			Vector<double> ScalarProduct(const Vector<double> & weights, WeakVector<const double> values, WeakFactor factor) const;
			template <class OTHER> Vector<double> ScalarProductImpl(const Vector<double> & weights, WeakVector<const OTHER> values, WeakFactor factor) const;

		public:
			// Construction
			WeakVectorVariable(WeakVector<TYPE> values);
			~WeakVectorVariable();
		};

		// Construction
		template <class TYPE>
		WeakVectorVariable<TYPE>::WeakVectorVariable(WeakVector<TYPE> values)
			: values(values)
		{
		}

		template <class TYPE>
		WeakVectorVariable<TYPE>::~WeakVectorVariable()
		{
		}

		// Operations
		template <class TYPE>
		void WeakVectorVariable<TYPE>::UpdatePredictor(Vector<double> & eta, double beta) const
		{
			_ASSERT_ARGUMENT(eta.Size() == this->values.Size());
			for (int i = 0; i < this->values.Size(); ++i)
				eta(i) += this->values(i) * beta;
		}

		template <class TYPE>
		double WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & values) const
		{
			_ASSERT_ARGUMENT(values.Size() == this->values.Size());
			double sum = 0.0;
			for (int i = 0; i < this->values.Size(); ++i)
				sum += this->values(i) * values(i);
			return sum;
		}

		template <class TYPE> inline
		double WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable) const
		{
			// Double dispatch
			return variable->ScalarProduct(weights, this->values);
		}

		template <class TYPE>
		double WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & weights, WeakVector<const int> values) const
		{
			return this->ScalarProductImpl(weights, values);
		}

		template <class TYPE> inline
		double WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & weights, WeakVector<const double> values) const
		{
			return this->ScalarProductImpl(weights, values);
		}

		template <class TYPE> template <class OTHER>
		double WeakVectorVariable<TYPE>::ScalarProductImpl(const Vector<double> & weights, WeakVector<const OTHER> values) const
		{
			_ASSERT_ARGUMENT(weights.Size() == this->values.Size() && values.Size() == this->values.Size());
			double sum = 0.0;
			for (int i = 0; i < this->values.Size(); ++i)
				sum += this->values(i) * weights(i) * values(i);
			return sum;
		}

		// Stratified operations
		template <class TYPE>
		void WeakVectorVariable<TYPE>::UpdatePredictor(Vector<double> & eta, const Vector<double> & beta, WeakFactor factor) const
		{
			_ASSERT_ARGUMENT(eta.Size() == this->values.Size() && factor.Size() == this->values.Size() && beta.Size() == factor.NumberOfLevels());
			for (int i = 0; i < this->values.Size(); ++i)
			{
				const int level = factor.Level(i);
				eta(i) += this->values(i) * beta(level);
			}
		}

		template <class TYPE>
		Vector<double> WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & values, WeakFactor factor) const
		{
			_ASSERT_ARGUMENT(values.Size() == this->values.Size() && factor.Size() == this->values.Size());
			const int nlevels = factor.NumberOfLevels();
			Vector<double> sum(nlevels);
			for (int i = 0; i < this->values.Size(); ++i)
			{
				const int level = factor.Level(i);
				sum(level) += this->values(i) * values(i);
			}
			return sum;
		}

		template <class TYPE> inline
		Vector<double> WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable, WeakFactor factor) const
		{
			// Double dispatch
			return variable->ScalarProduct(weights, this->values, factor);
		}

		template <class TYPE> inline
		Vector<double> WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & weights, WeakVector<const int> values, WeakFactor factor) const
		{
			return this->ScalarProductImpl(weights, values, factor);
		}

		template <class TYPE> inline
		Vector<double> WeakVectorVariable<TYPE>::ScalarProduct(const Vector<double> & weights, WeakVector<const double> values, WeakFactor factor) const
		{
			return this->ScalarProductImpl(weights, values, factor);
		}

		template <class TYPE> template <class OTHER>
		Vector<double> WeakVectorVariable<TYPE>::ScalarProductImpl(const Vector<double> & weights, WeakVector<const OTHER> values, WeakFactor factor) const
		{
			_ASSERT_ARGUMENT(weights.Size() == this->values.Size() && values.Size() == this->values.Size() && factor.Size() == this->values.Size());
			const int nlevels = factor.NumberOfLevels();
			Vector<double> sum(nlevels);
			for (int i = 0; i < this->values.Size(); ++i)
			{
				const int level = factor.Level(i);
				sum(level) += this->values(i) * weights(i) * values(i);
			}
			return sum;
		}
	}
}

#endif
