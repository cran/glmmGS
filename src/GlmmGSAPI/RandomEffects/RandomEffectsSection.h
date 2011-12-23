#pragma once

#include "../Standard.h"
#include "../Section.h"

namespace GlmmGSAPI
{
	namespace RandomEffects
	{
		// RandomEffectsSection
		class RandomEffectsSection : public Section
		{
		private:
			// Implementation
			Pointer<Section> BeginBlock();
			Pointer<Section> BeginStratifiedBlock(WeakFactor factor);
			void EndRandomEffects();

		public:
			// Construction
			RandomEffectsSection(GlmmGSAPI & api);
			~RandomEffectsSection();
		};
	}
}
