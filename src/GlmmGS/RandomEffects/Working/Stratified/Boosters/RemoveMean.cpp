#include "../../../../Standard.h"
#include "RemoveMean.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				namespace Boosters
				{
					void RemoveMean::Reparameterize(Vector<double> & intercept)
					{
						const double mean = Mean(intercept);
						const int n = intercept.Size();
						for (int k = 0; k < n; ++k)
							intercept(k) -= mean;
					}
				}
			}
		}
	}
}
