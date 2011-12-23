#pragma once

#include "../Standard.h"
#include "Working/IBlock.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		// IFixedEffectsBlock
		class IBlock
		{
		protected:
			// Construction
			IBlock();
		public:
			virtual ~IBlock();

			// Properties
			virtual Pointer<Working::IBlock> CreateWorking() const = 0;
		};
	}
}
