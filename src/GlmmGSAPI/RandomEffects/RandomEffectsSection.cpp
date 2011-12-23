#include "../Standard.h"
#include "RandomEffectsSection.h"
#include "../GlmmGSAPI.h"
#include "Global/BlockSection.h"
#include "Stratified/BlockSection.h"

namespace GlmmGSAPI
{
	namespace RandomEffects
	{
		// RandomEffectsSection
		RandomEffectsSection::RandomEffectsSection(GlmmGSAPI & api)
			: Section(api)
		{
		}

		RandomEffectsSection::~RandomEffectsSection()
		{
		}

		Pointer<Section> RandomEffectsSection::BeginBlock()
		{
			return Pointer<Section>(new(bl) Global::BlockSection(this->api));
		}

		Pointer<Section> RandomEffectsSection::BeginStratifiedBlock(WeakFactor factor)
		{
			return Pointer<Section>(new(bl) Stratified::BlockSection(this->api, factor));
		}
	
		void RandomEffectsSection::EndRandomEffects()
		{
			// Do nothing
		}
	}
}
