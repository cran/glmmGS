#pragma once

#include "../../Standard.h"
#include "../../Section.h"

namespace GlmmGSAPI
{
	namespace RandomEffects
	{
		namespace Global
		{
			// BlockSection
			class BlockSection : public Section
			{
			private:
				// Fields
				Vector<Pointer<GlmmGS::Variables::IVariable> > variables;
				Pointer<GlmmGS::RandomEffects::Global::CovarianceModels::ICovarianceModel> covariance_model;

				// Implementation
				void AddIntercept();
				void AddCovariate(WeakVector<const int> values);
				void AddCovariate(WeakVector<const double> values);
				void AddIdentityCovarianceModel();
				void AddPrecisionModel(WeakMatrix<const double> precision);
				void EndBlock();

			public:
				// Constructor
				BlockSection(GlmmGSAPI & api);
				~BlockSection();
			};
		}
	}
}
