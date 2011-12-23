#pragma once

#include "../Standard.h"
#include "IResponse.h"

namespace GlmmGS
{
	namespace Responses
	{
		// PoissonResponse
		class PoissonResponse : public IResponse
		{
		private:
			// Fields
			WeakVector<const int> response;

		public:
			// Construction
			PoissonResponse(WeakVector<const int> response);
			~PoissonResponse();

			// Properties
			int NumberOfObservations() const;

			// Methods
			void EvaluateWorkingWeightsAndValues(Vector<double> & weights, Vector<double> & values, const Vector<double> & eta) const;
		};
	}
}
