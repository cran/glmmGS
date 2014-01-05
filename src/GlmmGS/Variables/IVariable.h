#ifndef GLMMGS_UTILITIES_VARIABLES_IVARIABLE_H
#define GLMMGS_UTILITIES_VARIABLES_IVARIABLE_H

#include "../Standard.h"

namespace GlmmGS
{
	namespace Variables
	{
		// IVariable
		class IVariable
		{
			// Friends
			friend class Intercept;
			friend class StratifiedIntercept;
			template <class TYPE> friend class WeakVectorVariable;
			friend double ScalarProduct(Pointer<IVariable> variable, const Vector<double> & values);
			friend double ScalarProduct(Pointer<IVariable> variable1, const Vector<double> & weights, Pointer<IVariable> variable2);
			friend Utilities::Vector<double> ScalarProduct(Pointer<IVariable> variable, const Vector<double> & values, WeakFactor factor);
			friend Utilities::Vector<double> ScalarProduct(Pointer<IVariable> variable1, const Vector<double> & weights, Pointer<IVariable> variable2, WeakFactor factor);

		private:
			// Operations
			virtual double ScalarProduct(const Vector<double> & values) const = 0;
			virtual double ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable) const = 0;
			virtual double ScalarProduct(const Vector<double> & weights, WeakVector<const int> values) const = 0;
			virtual double ScalarProduct(const Vector<double> & weights, WeakVector<const double> values) const = 0;

			// Stratified Operations
			virtual Vector<double> ScalarProduct(const Vector<double> & values, WeakFactor factor) const = 0;
			virtual Vector<double> ScalarProduct(const Vector<double> & weights, Pointer<IVariable> variable, WeakFactor factor) const = 0;
			virtual Vector<double> ScalarProduct(const Vector<double> & weights, WeakVector<const int> values, WeakFactor factor) const = 0;
			virtual Vector<double> ScalarProduct(const Vector<double> & weights, WeakVector<const double> values, WeakFactor factor) const = 0;

		protected:
			// Construction
			IVariable();
		public:
			virtual ~IVariable();

			// Methods
			virtual void UpdatePredictor(Vector<double> & eta, double beta) const = 0;
			// Stratified methods
			virtual void UpdatePredictor(Vector<double> & eta, const Vector<double> & beta, WeakFactor factor) const = 0;
		};

		// Operations (friend functions)
		inline
		double ScalarProduct(Pointer<IVariable> variable, const Vector<double> & values)
		{
			return variable->ScalarProduct(values);
		}
	
		inline
		double ScalarProduct(Pointer<IVariable> variable1, const Vector<double> & weights, Pointer<IVariable> variable2)
		{
			return variable1->ScalarProduct(weights, variable2);
		}
	
		// Stratified Operations (friend functions)
		inline
		Vector<double> ScalarProduct(Pointer<IVariable> variable, const Vector<double> & values, WeakFactor factor)
		{
			return variable->ScalarProduct(values, factor);
		}

		inline
		Vector<double> ScalarProduct(Pointer<IVariable> variable1, const Vector<double> & weights, Pointer<IVariable> variable2, WeakFactor factor)
		{
			return variable1->ScalarProduct(weights, variable2, factor);
		}
	}
}

#endif
