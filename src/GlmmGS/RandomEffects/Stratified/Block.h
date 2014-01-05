#ifndef GLMMGS_RANDOMEFFECTS_STRATIFIED_BLOCK_H
#define GLMMGS_RANDOMEFFECTS_STRATIFIED_BLOCK_H

#include "../../Standard.h"
#include "../../Variables/IVariable.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "../Working/IBlock.h"
#include "../Working/Stratified/Boosters/IBooster.h"
#include "../IBlock.h"

namespace GlmmGS
{
	namespace RandomEffects
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
				Pointer<CovarianceModels::ICovarianceModel> covariance_model;
				Pointer<Working::Stratified::Boosters::IBooster> booster;

				// Implementation
				Pointer<Working::IBlock> CreateWorking() const;

			public:
				// Construction
				Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Pointer<Working::Stratified::Boosters::IBooster> booster);
				~Block();
			};
		}
	}
}

#endif
