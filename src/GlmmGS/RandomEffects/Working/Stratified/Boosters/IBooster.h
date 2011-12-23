#pragma once

#include "../../../../Standard.h"

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
					class IBooster
					{
					public:
						virtual void Reparameterize(Vector<double> & intercept) = 0;
					};
				}
			}
		}
	}
}
