#ifndef GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_BOOSTERS_DEFAULT_H
#define GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_BOOSTERS_DEFAULT_H

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
					class Default : public IBooster
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
