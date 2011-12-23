#include "../../../Standard.h"
#include "../../../Estimate.h"
#include "Coefficients.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Working
		{
			namespace Global
			{
				Coefficients::Coefficients(int size) :
					values(size)
				{
				}

				Coefficients::~Coefficients()
				{
				}

				Vector<Estimate> Coefficients::Estimates() const
				{
					const int n = this->values.Size();
					Vector<Estimate> y(n);
					TriangularMatrix<double> covariance = this->precision.Inverse();
					for (int i = 0; i < n; ++i)
						y(i) = Estimate(this->values(i), covariance(i, i));
					return y;
				}

				int Coefficients::Update(const TriangularMatrix<double> & precision, const Vector<double> & jacobian, Comparer comparer)
				{
					// Decompose precision
					this->precision.Decompose(precision);

					// Evaluate update
					Vector<double> h = this->precision.Solve(jacobian);

					// Debug
					Print("MaxAbs update fixed effects: %g\n", MaxAbs(h));

					// Check if update is significant
					int update = 1;
					if (comparer.IsZero(h, this->values))
						update = 0;

					// Update
					this->values += h;

					return update;
				}
			}
		}
	}
}
