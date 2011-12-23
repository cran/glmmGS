#include "../../../Standard.h"
#include "../../../Estimate.h"
#include "Coefficients.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				// Construction
				Coefficients::Coefficients(int nvariables, int nlevels)
					: size(nvariables * nlevels), values(nvariables)
				{
					for (int i = 0; i < nvariables; ++i)
						this->values(i).Size(nlevels);
				}

				Coefficients::~Coefficients()
				{
				}

				// Properties
				Vector<Estimate> Coefficients::Estimates() const
				{
					const int nvars = this->values.Size();
					const int nlevels = nvars > 0 ? this->values(0).Size() : 0;
					Vector<Estimate> y(nvars * nlevels);
					TriangularMatrix<Vector<double> > covariance = this->precision.Inverse();
					for (int index = 0, i = 0; i < nvars; ++i)
					{
						const Vector<double> & valuei = this->values(i);
						const Vector<double> & diagi = covariance(i, i);
						for (int j = 0; j < nlevels; ++j, ++index)
							y(index) = Estimate(valuei(j), diagi(j));
					}
					return y;
				}

				// Methods
				int Coefficients::Update(const TriangularMatrix<Vector<double> > & precision, const Vector<Vector<double> > & jacobian, Comparer comparer)
				{
					// Decompose precision
					this->precision.Decompose(precision);

					// Evaluate update
					Vector<Vector<double> > h = this->precision.Solve(jacobian);

					// Debug
					Print("MaxAbs update fixed effects: %g\n", MaxAbs(h));

					// Check if update is significant
					int update = 1;
					if (comparer.IsZero(h, this->values))
						update = 0;

					// Update
					for (int i = 0; i < h.Size(); ++i)
						this->values(i) += h(i);

					return update;
				}
			}
		}
	}
}
