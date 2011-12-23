#pragma once

#include "../../Standard.h"
#include "../../Section.h"

namespace GlmmGSAPI
{
	namespace FixedEffects
	{
		namespace Global
		{
			// BlockSection
			class BlockSection : public Section
			{
			private:
				// Fields
				Vector<Pointer<GlmmGS::Variables::IVariable> > variables;

				// Implementation
				void AddIntercept();
				void AddCovariate(WeakVector<const int> values);
				void AddCovariate(WeakVector<const double> values);
				void EndBlock();

			public:
				// Construction
				BlockSection(GlmmGSAPI & api);
				~BlockSection();
			};
		}
	}
}
