#include "GlmmGSAPI.h"
#include "Section.h"
#include "Responses/BinomialResponseSection.h"
#include "FixedEffects/FixedEffectsSection.h"
#include "RandomEffects/RandomEffectsSection.h"
#include "Exceptions/Exceptions.h"
#include "../GlmmGS/Estimate.h"

namespace GlmmGSAPI
{
	// The application
	GlmmGSAPI the_api;

	// GlmmGSAPI
	GlmmGSAPI::GlmmGSAPI()
		: last_error(error_buffer_size), iterations(-1), fixed_intercept(false)
	{
	}

	GlmmGSAPI::~GlmmGSAPI()
	{
	}

	void GlmmGSAPI::SetLastError(const Exception & e)
	{
		this->last_error.Append(e.Message());
	}

	void GlmmGSAPI::GetLastError(char * buffer, int size)
	{
		if (size > 0)
		{
			int length = Min(size - 1, this->last_error.Length());
			memcpy(buffer, this->last_error.Pointer(), length);
			buffer[length]= 0;
			this->last_error.Empty();
		}
	}

	void GlmmGSAPI::Begin()
	{
		if (this->sections.IsEmpty() == false)
			throw Exception("Invalid call: Begin");
		this->ForceEnd(); // This should not be necessary, but it is better to
						  // clean up twice rather than none
		this->sections.Push(Pointer<Section>(new(bl) Section(*this)));
	}

	void GlmmGSAPI::End()
	{
		this->sections.Pop();
		if (this->sections.IsEmpty() == false)
			throw Exception("Invalid call: End");

		// Reset
		this->last_error.Empty();
		this->response.Reset();
		this->offset.Reset();
		this->fixed_effects.Free();
		this->random_effects.Free();
		this->fixed_intercept = false;
	}

	void GlmmGSAPI::ForceEnd()
	{
		// Reset
		this->sections.Free();
		this->last_error.Empty();
		this->response.Reset();
		this->offset.Reset();
		this->fixed_effects.Free();
		this->random_effects.Free();
		this->fixed_intercept = false;
	}

	void GlmmGSAPI::BeginResponse(WeakString<const char> family)
	{
		Pointer<Section> section = this->sections.Top()->BeginResponse(family);
		this->sections.Push(section);
	}

	void GlmmGSAPI::EndResponse()
	{
		this->sections.Top()->EndResponse();
		this->sections.Pop();
	}

	void GlmmGSAPI::BeginFixedEffects()
	{
		Pointer<Section> section = this->sections.Top()->BeginFixedEffects();
		this->sections.Push(section);
	}

	void GlmmGSAPI::EndFixedEffects()
	{
		this->sections.Top()->EndFixedEffects();
		this->sections.Pop();
	}

	void GlmmGSAPI::BeginRandomEffects()
	{
		Pointer<Section> section = this->sections.Top()->BeginRandomEffects();
		this->sections.Push(section);
	}

	void GlmmGSAPI::EndRandomEffects()
	{
		this->sections.Top()->EndRandomEffects();
		this->sections.Pop();
	}

	void GlmmGSAPI::BeginGlobalBlock()
	{
		Pointer<Section> section = this->sections.Top()->BeginBlock();
		this->sections.Push(section);
	}

	void GlmmGSAPI::EndGlobalBlock()
	{
		this->sections.Top()->EndBlock();
		this->sections.Pop();
	}

	void GlmmGSAPI::BeginStratifiedBlock(WeakFactor factor)
	{
		Pointer<Section> section = this->sections.Top()->BeginStratifiedBlock(factor);
		this->sections.Push(section);
	}

	void GlmmGSAPI::EndStratifiedBlock()
	{
		this->sections.Top()->EndStratifiedBlock();
		this->sections.Pop();
	}

	void GlmmGSAPI::AddResponse(WeakVector<const int> values)
	{
		this->sections.Top()->AddResponse(values);
	}

	void GlmmGSAPI::AddCounts(WeakVector<const int> values)
	{
		this->sections.Top()->AddCounts(values);
	}
	
	void GlmmGSAPI::AddOffset(WeakVector<const int> values)
	{
		this->sections.Top()->AddOffset(values);
	}

	void GlmmGSAPI::AddOffset(WeakVector<const double> values)
	{
		this->sections.Top()->AddOffset(values);
	}

	void GlmmGSAPI::AddIntercept()
	{
		this->sections.Top()->AddIntercept();
	}

	void GlmmGSAPI::AddCovariate(WeakVector<const int> values)
	{
		this->sections.Top()->AddCovariate(values);
	}
	
	void GlmmGSAPI::AddCovariate(WeakVector<const double> values)
	{
		this->sections.Top()->AddCovariate(values);
	}

	// Covariance models
	void GlmmGSAPI::AddIdentityCovarianceModel()
	{
		this->sections.Top()->AddIdentityCovarianceModel();
	}

	void GlmmGSAPI::AddPrecisionModel(WeakMatrix<const double> precision)
	{
		this->sections.Top()->AddPrecisionModel(precision);
	}

	void GlmmGSAPI::AddSparsePrecisionModel(const LDL::SparseMatrix<double> & precision)
	{
		this->sections.Top()->AddSparsePrecisionModel(precision);
	}

	// Fit
	void GlmmGSAPI::Fit(GlmmGS::Controls controls)
	{
		// Set offset to ZeroOffset if no offset was specified
		if (this->offset.IsNull())
			this->offset.Reset(new(bl) GlmmGS::Offsets::ZeroOffset());

		// Reset results
		this->fixed_effects_estimates = Vector<GlmmGS::Estimate>();
		this->random_effects_estimates = Vector<GlmmGS::Estimate>();
		this->covariance_components_estimates = Vector<GlmmGS::Estimate>();
		this->iterations = -1;

		// Fit the model
		GlmmGS::GlmmGS glmmGS;
		glmmGS.Fit(this->response, this->offset, this->fixed_effects, this->random_effects, controls);

		// Set results
		this->fixed_effects_estimates = glmmGS.FixedEffectsCoefficients();
		this->random_effects_estimates = glmmGS.RandomEffectsCoefficients();
		this->covariance_components_estimates = glmmGS.CovarianceComponents();
		this->iterations = glmmGS.Iterations();
	}

	// Results
	int GlmmGSAPI::GetFixedEffectsSize() const
	{
		return this->fixed_effects_estimates.Size();
	}

	void GlmmGSAPI::GetFixedEffectsEstimates(WeakVector<double> values) const
	{
		if (values.Size() != this->fixed_effects_estimates.Size())
			throw Exceptions::InvalidSizeException();
		for (int i = 0; i < this->fixed_effects_estimates.Size(); ++i)
			values(i) = this->fixed_effects_estimates(i).Value();
	}

	void GlmmGSAPI::GetFixedEffectsErrors(WeakVector<double> values) const
	{
		if (values.Size() != this->fixed_effects_estimates.Size())
			throw Exceptions::InvalidSizeException();
		for (int i = 0; i < this->fixed_effects_estimates.Size(); ++i)
			values(i) = sqrt(this->fixed_effects_estimates(i).Variance());
	}

	int GlmmGSAPI::GetRandomEffectsSize() const
	{
		return this->random_effects_estimates.Size();
	}

	void GlmmGSAPI::GetRandomEffectsEstimates(WeakVector<double> values) const
	{
		if (values.Size() != this->random_effects_estimates.Size())
			throw Exceptions::InvalidSizeException();
		for (int i = 0; i < this->random_effects_estimates.Size(); ++i)
			values(i) = this->random_effects_estimates(i).Value();
	}

	void GlmmGSAPI::GetRandomEffectsErrors(WeakVector<double> values) const
	{
		if (values.Size() != this->random_effects_estimates.Size())
			throw Exceptions::InvalidSizeException();
		for (int i = 0; i < this->random_effects_estimates.Size(); ++i)
			values(i) = sqrt(this->random_effects_estimates(i).Variance());
	}

	int GlmmGSAPI::GetCovarianceComponentsSize() const
	{
		return this->covariance_components_estimates.Size();
	}

	void GlmmGSAPI::GetCovarianceComponentsEstimates(WeakVector<double> values) const
	{
		if (values.Size() != this->covariance_components_estimates.Size())
			throw Exceptions::InvalidSizeException();
		for (int i = 0; i < this->covariance_components_estimates.Size(); ++i)
			values(i) = this->covariance_components_estimates(i).Value();
	}

	void GlmmGSAPI::GetCovarianceComponentsErrors(WeakVector<double> values) const
	{
		if (values.Size() != this->covariance_components_estimates.Size())
			throw Exceptions::InvalidSizeException();
		for (int i = 0; i < this->covariance_components_estimates.Size(); ++i)
			values(i) = sqrt(this->covariance_components_estimates(i).Variance());
	}

	int GlmmGSAPI::GetIterations() const
	{
		return this->iterations;
	}
}
