#pragma once

#include "../../Standard.h"
#include "../../Variables/IVariable.h"
#include "../IBlock.h"
#include "../Working/IBlock.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Stratified
		{
			// Block
			class Block : public IBlock
			{
			private:
				// Fields
				Vector<Pointer<Variables::IVariable> > variables;
				WeakFactor factor;

				// Implementation
				Pointer<Working::IBlock> CreateWorking() const;

			public:
				// Construction
				Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor);
				~Block();
			};
		}
	}
}
