#include "../../Standard.h"
#include "../../Variables/IVariable.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "../Working/IBlock.h"
#include "../Working/Stratified/Block.h"
#include "../Working/Stratified/Boosters/IBooster.h"
#include "Block.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Stratified
		{
			// Construction
			Block::Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Pointer<Working::Stratified::Boosters::IBooster> booster)
				: variables(variables), factor(factor), covariance_model(covariance_model), booster(booster)
			{
			}

			Block::~Block()
			{
			}

			// Implementation
			Pointer<Working::IBlock> Block::CreateWorking() const
			{
				typedef Working::Stratified::Block T;
				return Pointer<T>(new(bl) T(this->variables, this->factor, this->covariance_model->CreateWorking(), this->booster));
			}
		}
	}
}
