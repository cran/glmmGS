#include "../../Standard.h"
#include "../../GlmmGSAPI.h"
#include "../../Exceptions/Exceptions.h"
#include "BlockSection.h"

namespace GlmmGSAPI
{
	namespace RandomEffects
	{
		namespace Stratified
		{
			// BlockSection
			BlockSection::BlockSection(GlmmGSAPI & api, WeakFactor factor)
				: Section(api), factor(factor), booster(new(bl) GlmmGS::RandomEffects::Working::Stratified::Boosters::Default)
			{
			}

			BlockSection::~BlockSection()
			{
			}

			void BlockSection::AddIntercept()
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::NoVariableAfterCovarianceModelException();

				if (this->api.fixed_intercept == true)
					this->booster.Reset(new(bl) GlmmGS::RandomEffects::Working::Stratified::Boosters::RemoveMean);

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
				typedef GlmmGS::RandomEffects::Stratified::CovarianceModels::IdentityModel T;
				this->covariance_model.Reset(new(bl) T(this->variables.Size(), this->factor.NumberOfLevels()));
			}

			void BlockSection::AddPrecisionModel(WeakMatrix<const double> precision)
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::MultipleCovarianceModelsException();

				// Add covariance model
				typedef GlmmGS::RandomEffects::Stratified::CovarianceModels::PrecisionModel T;
				this->covariance_model.Reset(new(bl) T(this->variables.Size(), precision));
			}

			void BlockSection::AddSparsePrecisionModel(const LDL::SparseMatrix<double> & precision)
			{
				if (this->covariance_model.IsNull() == false)
					throw Exceptions::MultipleCovarianceModelsException();

				// Add sparse covariance model
				typedef GlmmGS::RandomEffects::Stratified::CovarianceModels::SparsePrecisionModel T;
				this->covariance_model.Reset(new(bl) T(this->variables.Size(), precision));
			}

			void BlockSection::EndStratifiedBlock()
			{
				if (this->covariance_model.IsNull() == true)
					throw Exceptions::NoCovarianceModelException();

				// Add random effect block to random effects;
				typedef GlmmGS::RandomEffects::Stratified::Block T;
				this->api.random_effects.Add(Pointer<T>(new(bl) T(this->variables, this->factor, this->covariance_model, this->booster)));
			}
		}
	}
}
