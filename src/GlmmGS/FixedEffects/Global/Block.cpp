#include "../../Standard.h"
#include "../../Variables/IVariable.h"
#include "../Working/IBlock.h"
#include "../Working/Global/Block.h"
#include "Block.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Global
		{
			// Construction
			Block::Block(Vector<Pointer<Variables::IVariable> > variables) :
				variables(variables)
			{
			}

			Block::~Block()
			{
			}

			// Implementation
			Pointer<Working::IBlock> Block::CreateWorking() const
			{
				typedef Working::Global::Block T;
				return Pointer<T>(new(bl) T(this->variables));
			}
		}
	}
}
