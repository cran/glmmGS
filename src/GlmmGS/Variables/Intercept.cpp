#include "../Standard.h"
#include "IVariable.h"
#include "Intercept.h"

namespace GlmmGS
{
	namespace Variables
	{
		// Intercept
		Intercept::Intercept()
		{
		}

		Intercept::~Intercept()
		{
		}

		// Operations
		void Intercept::UpdatePredictor(Vector<double> & eta, double beta) const
		{
			const int n = eta.Size();
			for (int i = 0; i < n; ++i)
				eta(i) += beta;
		}

		double Intercept::ScalarProduct(const Vector<double> & values) const
		{
			const int n = values.Size();
			double sum = 0.0;
			for (int i = 0; i < n; ++i)
				sum += values(i);
			return sum;
		}

		// Stratified operations
		void Intercept::UpdatePredictor(Vector<double> & eta, const Vector<double> & beta, WeakFactor factor) const
		{
			_ASSERT_ARGUMENT(eta.Size() == factor.Size() && beta.Size() == factor.NumberOfLevels());
			const int n = eta.Size();
			for (int i = 0; i < n; ++i)
			{
				const int level = factor.Level(i);
				eta(i) += beta(level);
			}
		}

		Vector<double> Intercept::ScalarProduct(const Vector<double> & values, WeakFactor factor) const
		{
			_ASSERT_ARGUMENT(values.Size() == factor.Size());
			const int n = values.Size();
			const int nlevels = factor.NumberOfLevels();
			Vector<double> sum(nlevels);
			for (int i = 0; i < n; ++i)
			{
				const int level = factor.Level(i);
				sum(level) += values(i);
			}
			return sum;
		}
	}
}
