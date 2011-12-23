#include "../../Standard.h"
#include "../../GlmmGSAPI.h"
#include "BlockSection.h"

namespace GlmmGSAPI
{
	namespace FixedEffects
	{
		namespace Stratified
		{
			// BlockSection
			BlockSection::BlockSection(GlmmGSAPI & api, WeakFactor factor)
				: Section(api), factor(factor)
			{
			}

			BlockSection::~BlockSection()
			{
			}

			void BlockSection::AddIntercept()
			{
				this->api.fixed_intercept = true;
				typedef GlmmGS::Variables::Intercept T;
				this->variables.Add(Pointer<T>(new(bl) T));
			}

			void BlockSection::AddCovariate(WeakVector<const int> values)
			{
				typedef GlmmGS::Variables::WeakVectorVariable<const int> T;
				this->variables.Add(Pointer<T>(new(bl) T(values)));
			}

			void BlockSection::AddCovariate(WeakVector<const double> values)
			{
				typedef GlmmGS::Variables::WeakVectorVariable<const double> T;
				this->variables.Add(Pointer<T>(new(bl) T(values)));
			}

			void BlockSection::EndStratifiedBlock()
			{
				typedef GlmmGS::FixedEffects::Stratified::Block T;
				this->api.fixed_effects.Add(Pointer<T>(new(bl) T(this->variables, this->factor)));
			}
		}
	}
}
