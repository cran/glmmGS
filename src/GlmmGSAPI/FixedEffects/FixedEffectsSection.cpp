#include "../Standard.h"
#include "FixedEffectsSection.h"
#include "../GlmmGSAPI.h"
#include "Global/BlockSection.h"
#include "Stratified/BlockSection.h"

namespace GlmmGSAPI
{
	namespace FixedEffects
	{
		// FixedEffectsSection
		FixedEffectsSection::FixedEffectsSection(GlmmGSAPI & api)
			: Section(api)
		{
		}

		FixedEffectsSection::~FixedEffectsSection()
		{
		}

		Pointer<Section> FixedEffectsSection::BeginBlock()
		{
			return Pointer<Section>(new(bl) Global::BlockSection(this->api));
		}

		Pointer<Section> FixedEffectsSection::BeginStratifiedBlock(WeakFactor factor)
		{
			return Pointer<Section>(new(bl) Stratified::BlockSection(this->api, factor));
		}
	
		void FixedEffectsSection::EndFixedEffects()
		{
			// Do nothing
		}
	}
}
