#include "../../Standard.h"
#include "../../GlmmGSAPI.h"
#include "../../Exceptions/Exceptions.h"
#include "BlockSection.h"

namespace GlmmGSAPI
{
	namespace RandomEffects
	{
		namespace Global
		{
			// Construction
			BlockSection::BlockSection(GlmmGSAPI & api)
				: Section(api)
			{
			}

			BlockSection::~BlockSection()
			{
			}

			// Implementation
			void BlockSection::AddIntercept()
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::NoVariableAfterCovarianceModelException();

				// Add intercept
				typedef GlmmGS::Variables::Intercept T;
				this->variables.Add(Pointer<T>(new(bl) T));
			}

			void BlockSection::AddCovariate(WeakVector<const int> values)
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::NoVariableAfterCovarianceModelException();

				// Add covariate
				typedef GlmmGS::Variables::WeakVectorVariable<const int> T;
				this->variables.Add(Pointer<T>(new(bl) T(values)));
			}

			void BlockSection::AddCovariate(WeakVector<const double> values)
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::NoVariableAfterCovarianceModelException();

				// Add covariate
				typedef GlmmGS::Variables::WeakVectorVariable<const double> T;
				this->variables.Add(Pointer<T>(new(bl) T(values)));
			}

			void BlockSection::AddIdentityCovarianceModel()
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::MultipleCovarianceModelsException();

				// Add covariance model
				typedef GlmmGS::RandomEffects::Global::CovarianceModels::IdentityModel T;
				this->covariance_model.Reset(new(bl) T(this->variables.Size()));
			}

			void BlockSection::AddPrecisionModel(WeakMatrix<const double> precision)
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::MultipleCovarianceModelsException();

				// Add covariance model
				typedef GlmmGS::RandomEffects::Global::CovarianceModels::PrecisionModel T;
				this->covariance_model.Reset(new(bl) T(precision));
			}

			void BlockSection::EndBlock()
			{
				if (this->covariance_model.IsNull() == true)
					throw Exceptions::NoCovarianceModelException();

				// Add random effect block to random effects;
				typedef GlmmGS::RandomEffects::Global::Block T;
				this->api.random_effects.Add(Pointer<T>(new(bl) T(this->variables, this->covariance_model)));
			}
		}
	}
}
