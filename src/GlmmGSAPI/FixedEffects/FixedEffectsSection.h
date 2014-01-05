#ifndef GLMMGSAPI_FIXEDEFFECTS_FIXEDEFFECTSSECTION_H
#define GLMMGSAPI_FIXEDEFFECTS_FIXEDEFFECTSSECTION_H

#include "../Standard.h"
#include "../Section.h"

namespace GlmmGSAPI
{
	namespace FixedEffects
	{
		// FixedEffectsSection
		class FixedEffectsSection : public Section
		{
		private:
			// Implementation
			Pointer<Section> BeginBlock();
			Pointer<Section> BeginStratifiedBlock(WeakFactor factor);
			void EndFixedEffects();

		public:
			// Construction
			FixedEffectsSection(GlmmGSAPI & api);
			~FixedEffectsSection();
		};
	}
}

#endif
