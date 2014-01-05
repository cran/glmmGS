#ifndef GLMMGS_FIXEDEFFECTS_WORKING_STRATIFIED_BLOCK_H
#define GLMMGS_FIXEDEFFECTS_WORKING_STRATIFIED_BLOCK_H

#include "../../../Standard.h"
#include "../../../Variables/IVariable.h"
#include "../../../Estimate.h"
#include "../IBlock.h"
#include "Coefficients.h"

namespace GlmmGS
{
	namespace FixedEffects
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

					// Implementation
					Vector<Estimate> Coefficients() const;
					int UpdateCoefficients(const Vector<double> & w, const Vector<double> & z, Comparer comparer);
					void UpdatePredictor(Vector<double> & eta) const;

				public:
					// Construction
					Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor);
					~Block();
				};
			}
		}
	}
}

#endif
