#ifndef GLMMGS_UTILITIES_VARIABLES_INTERCEPT_H
#define GLMMGS_UTILITIES_VARIABLES_INTERCEPT_H

#include "../Standard.h"
#include "IVariable.h"

namespace GlmmGS
{
	namespace Variables
	{
		// Intercept
		class Intercept : public IVariable
		{
		private:
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
			Intercept();
			~Intercept();
		};

		// Operations
		inline
		double Intercept::ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable) const
		{
			// Double dispatch
			return variable->ScalarProduct(weights);
		}

		inline
		double Intercept::ScalarProduct(const Vector<double> & weights, WeakVector<const int> values) const
		{
			return this->ScalarProductImpl(weights, values);
		}

		inline
		double Intercept::ScalarProduct(const Vector<double> & weights, WeakVector<const double> values) const
		{
			return this->ScalarProductImpl(weights, values);
		}

		template <class OTHER>
		double Intercept::ScalarProductImpl(const Vector<double> & weights, WeakVector<const OTHER> values) const
		{
			_ASSERT_ARGUMENT(weights.Size() == values.Size());
			const int n = values.Size();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += weights(i) * values(i);
			return sum;
		}
	
		// Stratified Operations
		inline
		Vector<double> Intercept::ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable, WeakFactor factor) const
		{
			// Double dispatch
			return variable->ScalarProduct(weights, factor);
		}

		inline
		Vector<double> Intercept::ScalarProduct(const Vector<double> & weights, WeakVector<const int> values, WeakFactor factor) const
		{
			return this->ScalarProductImpl(weights, values, factor);
		}

		inline
		Vector<double> Intercept::ScalarProduct(const Vector<double> & weights, WeakVector<const double> values, WeakFactor factor) const
		{
			return this->ScalarProductImpl(weights, values, factor);
		}
	
		template <class OTHER>
		Vector<double> Intercept::ScalarProductImpl(const Vector<double> & weights, WeakVector<const OTHER> values, WeakFactor factor) const
		{
			_ASSERT_ARGUMENT(weights.Size() == values.Size() && factor.Size() == values.Size());
			const int n = values.Size();
			const int nlevels = factor.NumberOfLevels();
			Vector<double> sum(nlevels);
			for (int i = 0; i < n; ++i)
			{
				const int level = factor.Level(i);
				sum(level) += weights(i) * values(i);
			}
			return sum;
		}
	}
}

#endif
