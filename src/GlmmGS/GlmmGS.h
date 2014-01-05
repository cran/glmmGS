#ifndef GLMMGS_GLMMGS_H
#define GLMMGS_GLMMGS_H

#include "Standard.h"
#include "Responses/IResponse.h"
#include "Offsets/IOffset.h"
#include "FixedEffects/IBlock.h"
#include "RandomEffects/IBlock.h"
#include "Controls.h"
#include "Estimate.h"

namespace GlmmGS
{
	// GlmmGS
	class GlmmGS
	{
		// Fields
		Controls controls;
		Vector<Estimate> fixed_effects_estimates;
		Vector<Estimate> random_effects_estimates;
		Vector<Estimate> covariance_components_estimates;
		int iterations;

	public:
		// Construction
		GlmmGS();

		// Properties
		const Vector<Estimate> & FixedEffectsCoefficients() const;
		const Vector<Estimate> & RandomEffectsCoefficients() const;
		const Vector<Estimate> & CovarianceComponents() const;
		int Iterations() const;

		// Methods
		void Fit(const Pointer<Responses::IResponse> & y,
				const Pointer<Offsets::IOffset> & offset,
				const Vector<Pointer<FixedEffects::IBlock> > & x,
				const Vector<Pointer<RandomEffects::IBlock> > & z,
				const Controls & controls);
	};

	inline
	const Vector<Estimate> & GlmmGS::FixedEffectsCoefficients() const
	{
		return this->fixed_effects_estimates;
	}

	inline
	const Vector<Estimate> & GlmmGS::RandomEffectsCoefficients() const
	{
		return this->random_effects_estimates;
	}

	inline
	const Vector<Estimate> & GlmmGS::CovarianceComponents() const
	{
		return this->covariance_components_estimates;
	}

	inline
	int GlmmGS::Iterations() const
	{
		return this->iterations;
	}
}

#endif
