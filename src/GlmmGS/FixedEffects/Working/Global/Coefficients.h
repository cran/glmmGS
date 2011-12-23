#pragma once

#include "../../../Standard.h"
#include "../../../Estimate.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Working
		{
			namespace Global
			{
				// Coefficients
				class Coefficients
				{
				private:
					// Fields
					Vector<double> values;
					CholeskyDecomposition precision;

				public:
					// Construction
					Coefficients(int size);
					~Coefficients();

					// Properties
					int Size() const;
					double Value(int i) const;
					Vector<Estimate> Estimates() const;

					// Methods
					int Update(const TriangularMatrix<double> & precision, const Vector<double> & jacobian, Comparer comparer);
				};

				// Definition
				inline
				int Coefficients::Size() const
				{
					return this->values.Size();
				}

				inline
				double Coefficients::Value(int i) const
				{
					return this->values(i);
				}
			}
		}
	}
}
