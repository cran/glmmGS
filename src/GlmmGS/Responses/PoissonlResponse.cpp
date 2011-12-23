#include "../Standard.h"
#include "PoissonResponse.h"

namespace GlmmGS
{
	namespace Responses
	{
		// BinomialResponse
		PoissonResponse::PoissonResponse(WeakVector<const int> response) :
			response(response)
		{
		}

		PoissonResponse::~PoissonResponse()
		{
		}

		int PoissonResponse::NumberOfObservations() const
		{
			return this->response.Size();
		}

		void PoissonResponse::EvaluateWorkingWeightsAndValues(Vector<double> & weights, Vector<double> & values, const Vector<double> & eta) const
		{
			_ASSERT_ARGUMENT(this->response.Size() == weights.Size() &&
				this->response.Size() == values.Size() &&
				this->response.Size() == eta.Size());

			const int nobs = this->response.Size();

			for (int i = 0; i < nobs; ++i)
			{
				const double mu = exp(eta(i));
				values(i) = this->response(i) - mu; // First derivative in eta
				weights(i) = mu; // Minus the second derivative in eta
			}
		}
	}
}
