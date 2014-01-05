#ifndef GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_IBLOCK_H
#define GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_IBLOCK_H

#include "../../../Standard.h"
#include "../../../Variables/IVariable.h"
#include "../../../Estimate.h"
#include "../IBlock.h"
#include "Coefficients.h"
#include "Boosters/IBooster.h"
#include "CovarianceModels/ICovarianceModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
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
					Stratified::Coefficients beta;
					Pointer<CovarianceModels::ICovarianceModel> covariance_model;

					// Implementation
					Vector<Estimate> Coefficients() const;
					Vector<Estimate> CovarianceComponents() const;
					void UpdatePredictor(Vector<double> & eta) const;
					int Update(const Vector<double> & w, const Vector<double> & z, Comparer comparer);

				public:
					// Construction
					Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor, Pointer<CovarianceModels::ICovarianceModel> covariance_model, Pointer<Boosters::IBooster> booster);
				};
			}
		}
	}
}

#endif
