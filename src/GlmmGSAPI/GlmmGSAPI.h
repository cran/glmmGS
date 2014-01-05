#ifndef GLMMGSAPI_GLMMGSAPI_H
#define GLMMGSAPI_GLMMGSAPI_H

#include "Standard.h"
#include "Section.h"

namespace GlmmGSAPI
{
	// GlmmGSAPI
	class GlmmGSAPI
	{
	private:
		// Fields
		static const int error_buffer_size = 1024;
		Buffer last_error;
		Stack<Pointer<Section> > sections;
		Vector<GlmmGS::Estimate> fixed_effects_estimates; // Fixed-effects coefficients estimates
		Vector<GlmmGS::Estimate> random_effects_estimates; // Random-effects coefficients estimates
		Vector<GlmmGS::Estimate> covariance_components_estimates; // Variance component estimates
		int iterations;

	public:
		Pointer<GlmmGS::Responses::IResponse> response;
		Pointer<GlmmGS::Offsets::IOffset> offset;
		Vector<Pointer<GlmmGS::FixedEffects::IBlock> > fixed_effects;
		Vector<Pointer<GlmmGS::RandomEffects::IBlock> > random_effects;
		bool fixed_intercept;

	public:
		// Construction
		GlmmGSAPI();
		~GlmmGSAPI();

		// Error
		void SetLastError(const Exception & e);
		void GetLastError(char * buffer, int size);

		// Sections
		void Begin();
		void End();
		void ForceEnd();
		void BeginResponse(WeakString<const char> family);
		void EndResponse();
		void BeginFixedEffects();
		void EndFixedEffects();
		void BeginRandomEffects();
		void EndRandomEffects();
		void BeginGlobalBlock();
		void EndGlobalBlock();
		void BeginStratifiedBlock(WeakFactor factor);
		void EndStratifiedBlock();

		// Variables
		void AddResponse(WeakVector<const int> values);
		void AddCounts(WeakVector<const int> values);
		void AddOffset(WeakVector<const int> values);
		void AddOffset(WeakVector<const double> values);
		void AddIntercept();
		void AddCovariate(WeakVector<const int> values);
		void AddCovariate(WeakVector<const double> values);

		// Covariance models
		void AddIdentityCovarianceModel();
		void AddPrecisionModel(WeakMatrix<const double> precision);
		void AddSparsePrecisionModel(const LDL::SparseMatrix<double> & precision);

		// Fit
		void Fit(GlmmGS::Controls controls);

		// Results
		int GetFixedEffectsSize() const;
		void GetFixedEffectsEstimates(WeakVector<double> values) const;
		void GetFixedEffectsErrors(WeakVector<double> values) const;
		int GetRandomEffectsSize() const;
		void GetRandomEffectsEstimates(WeakVector<double> values) const;
		void GetRandomEffectsErrors(WeakVector<double> values) const;
		int GetCovarianceComponentsSize() const;
		void GetCovarianceComponentsEstimates(WeakVector<double> values) const;
		void GetCovarianceComponentsErrors(WeakVector<double> values) const;
		int GetIterations() const;
	};

	extern GlmmGSAPI the_api;
}

#endif
