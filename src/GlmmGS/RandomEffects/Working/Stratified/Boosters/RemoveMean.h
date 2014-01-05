#ifndef GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_BOOSTERS_REMOVEMEAN_H
#define GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_BOOSTERS_REMOVEMEAN_H

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

#endif
