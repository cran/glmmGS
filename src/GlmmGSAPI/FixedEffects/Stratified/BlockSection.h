#pragma once

#include "../../Standard.h"
#include "../../Section.h"

namespace GlmmGSAPI
{
	namespace FixedEffects
	{
		namespace Stratified
		{
			// BlockSection
			class BlockSection : public Section
			{
			private:
				// Fields
				WeakFactor factor;
				Vector<Pointer<GlmmGS::Variables::IVariable> > variables;

				// Implementation
				void AddIntercept();
				void AddCovariate(WeakVector<const int> values);
				void AddCovariate(WeakVector<const double> values);
				void EndStratifiedBlock();
	
			public:
				// Construction
				BlockSection(GlmmGSAPI & api, WeakFactor factor);
				~BlockSection();
			};
		}
	}
}
