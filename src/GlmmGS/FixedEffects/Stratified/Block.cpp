#include "../../Standard.h"
#include "../../Variables/IVariable.h"
#include "../Working/IBlock.h"
#include "../Working/Stratified/Block.h"
#include "Block.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Stratified
		{
			// Construction
			Block::Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor) :
				variables(variables), factor(factor)
			{
			}

			Block::~Block()
			{
			}

			// Implementation
			Pointer<Working::IBlock> Block::CreateWorking() const
			{
				typedef Working::Stratified::Block T;
				return Pointer<T>(new(bl) T(this->variables, this->factor));
			}
		}
	}
}
