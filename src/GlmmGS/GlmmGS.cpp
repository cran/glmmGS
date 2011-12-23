#include "Standard.h"
#include "GlmmGS.h"
#include "Responses/IResponse.h"
#include "FixedEffects/IBlock.h"
#include "RandomEffects/IBlock.h"
#include "GlmmGSSolver.h"

namespace GlmmGS
{
	// Helper function. TODO: move
	void ToVector(Vector<Estimate> & y, const Vector<Vector<Estimate> > & x)
	{
		// Calculate size
		int size = 0;
		for (int i = 0; i < x.Size(); ++i)
			size += x(i).Size();

		// Copy vectors
		y.Size(size);
		for (int index = 0, i = 0; i < x.Size(); ++i)
			for (int j = 0; j < x(i).Size(); ++j, ++index)
				y(index) = x(i)(j);
	}

	// GlmmGS
	GlmmGS::GlmmGS()
	{
	}

	// Properties
	// Methods
	void GlmmGS::Fit(const Pointer<Responses::IResponse> & y,
			const Pointer<Offsets::IOffset> & offset,
			const Vector<Pointer<FixedEffects::IBlock> > & x,
			const Vector<Pointer<RandomEffects::IBlock> > & z,
			const Controls & controls)
	{
		GlmmGSSolver solver;
		solver.Fit(y, offset, x, z, controls);

		Vector<Vector<Estimate> > beta = solver.FixedEffectsCoefficients();
		Vector<Vector<Estimate> > b = solver.RandomEffectsCoefficients();
		Vector<Vector<Estimate> > theta = solver.CovarianceComponents();
		this->iterations = solver.Iterations();

		ToVector(this->fixed_effects_estimates, beta);
		ToVector(this->random_effects_estimates, b);
		ToVector(this->covariance_components_estimates, theta);
	}
}
