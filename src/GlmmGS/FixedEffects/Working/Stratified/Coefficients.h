#pragma once

#include "../../../Standard.h"
#include "../../../Estimate.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				// Coefficients
				class Coefficients
				{
				private:
					// Fields
					int size;
					Vector<Vector<double> > values;
					VectorialCholeskyDecomposition precision;

				public:
					// Construction
					Coefficients(int nvariables, int nlevels);
					~Coefficients();

					// Properties
					int Size() const;
					const Vector<double> & Value(int i) const;
					Vector<Estimate> Estimates() const;

					// Methods
					int Update(const TriangularMatrix<Vector<double> > & precision, const Vector<Vector<double> > & jacobian, Comparer comparer);
				};

				// Properties
				inline
				int Coefficients::Size() const
				{
					return size;
				}

				inline
				const Vector<double> & Coefficients::Value(int i) const
				{
					return this->values(i);
				}
			}
		}
	}
}
