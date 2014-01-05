#ifndef GLMMGS_RANDOMEFFECTS_IBLOCK_H
#define GLMMGS_RANDOMEFFECTS_IBLOCK_H

#include "../Standard.h"
#include "Working/IBlock.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		// IBlock
		class IBlock
		{
		// Construction
		protected:
			IBlock();
		public:
			virtual ~IBlock();

			// Methods
			virtual Pointer<Working::IBlock> CreateWorking() const = 0;
		};
	}
}

#endif
