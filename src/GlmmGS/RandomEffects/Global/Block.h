#pragma once

#include "../../Standard.h"
#include "CovarianceModels/ICovarianceModel.h"
#include "../../Variables/IVariable.h"
#include "../IBlock.h"
#include "../Working/IBlock.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Global
		{
			// Block
			class Block : public IBlock
			{
			private:
				// Fields
				Vector<Pointer<Variables::IVariable> > variables;
				Pointer<CovarianceModels::ICovarianceModel> covariance_model;

				// Implementation
				Pointer<Working::IBlock> CreateWorking() const;

			public:
				// Construction
				Block(Vector<Pointer<Variables::IVariable> > variables, Pointer<CovarianceModels::ICovarianceModel> covariance_model);
				~Block();
			};
		}
	}
}
