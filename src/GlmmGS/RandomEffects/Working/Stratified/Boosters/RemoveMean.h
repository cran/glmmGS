#pragma once

#include "../../../../Standard.h"
#include "IBooster.h"

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
					class RemoveMean : public IBooster
					{
					public:
						void Reparameterize(Vector<double> & intercept);
					};
				}
			}
		}
	}
}
