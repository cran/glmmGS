#ifndef GLMMGS_FIXEDEFFECTS_GLOBAL_BLOCK_H
#define GLMMGS_FIXEDEFFECTS_GLOBAL_BLOCK_H

#include "../../Standard.h"
#include "../../Variables/IVariable.h"
#include "../IBlock.h"
#include "../Working/IBlock.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Global
		{
			// Block
			class Block : public IBlock
			{
			private:
				// Fields
				Vector<Pointer<Variables::IVariable> > variables;

				// Implementation
				Pointer<Working::IBlock> CreateWorking() const;

			public:
				// Construction
				Block(Vector<Pointer<Variables::IVariable> > variables);
				~Block();
			};
		}
	}
}

#endif
