#include "../../Standard.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "../Working/IBlock.h"
#include "../Working/Global/Block.h"
#include "Block.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Global
		{
			// Construction
			Block::Block(Vector<Pointer<Variables::IVariable> > variables, Pointer<CovarianceModels::ICovarianceModel> covariance_model) :
				variables(variables), covariance_model(covariance_model)
			{
			}

			Block::~Block()
			{
			}

			// Implementation
			Pointer<Working::IBlock> Block::CreateWorking() const
			{
				typedef Working::Global::Block T;
				return Pointer<T>(new(bl) T(this->variables, this->covariance_model->CreateWorking()));
			}
		}
	}
}
