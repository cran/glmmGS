#ifndef GLMMGSAPI_RANDOMEFFECTS_RANDOMEFFECTS_STRATIFIED_BLOCKSECTION_H
#define GLMMGSAPI_RANDOMEFFECTS_RANDOMEFFECTS_STRATIFIED_BLOCKSECTION_H

#include "../../Standard.h"
#include "../../Section.h"

namespace GlmmGSAPI
{
	namespace RandomEffects
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
				Pointer<GlmmGS::RandomEffects::Stratified::CovarianceModels::ICovarianceModel> covariance_model;
				Pointer<GlmmGS::RandomEffects::Working::Stratified::Boosters::IBooster> booster;

				// Implementation
				void AddIntercept();
				void AddCovariate(WeakVector<const int> values);
				void AddCovariate(WeakVector<const double> values);
				void AddIdentityCovarianceModel();
				void AddPrecisionModel(WeakMatrix<const double> precision);
				void AddSparsePrecisionModel(const LDL::SparseMatrix<double> & precision);
				void EndStratifiedBlock();

			public:
				// Construction
				BlockSection(GlmmGSAPI & api, WeakFactor factor);
				~BlockSection();
			};
		}
	}
}

#endif
