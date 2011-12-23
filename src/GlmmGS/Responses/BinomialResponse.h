#pragma once

#include "../Standard.h"
#include "IResponse.h"

namespace GlmmGS
{
	namespace Responses
	{
		// BinomialResponse
		class BinomialResponse : public IResponse
		{
		private:
			// Fields
			WeakVector<const int> response;
			WeakVector<const int> counts;

		public:
			// Construction
			BinomialResponse(WeakVector<const int> response, WeakVector<const int> counts);
			~BinomialResponse();

			// Properties
			int NumberOfObservations() const;

			// Methods
			void EvaluateWorkingWeightsAndValues(Vector<double> & weights, Vector<double> & values, const Vector<double> & eta) const;
		};
	}
}
