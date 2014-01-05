#ifndef GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_BOOSTERS_IBOOSTER_H
#define GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_BOOSTERS_IBOOSTER_H

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

#endif
