#include "../Standard.h"
#include "BinomialResponse.h"

namespace GlmmGS
{
	namespace Responses
	{
		// BinomialResponse
		BinomialResponse::BinomialResponse(WeakVector<const int> response, WeakVector<const int> counts) :
			response(response), counts(counts)
		{
			_VALIDATE_ARGUMENT(this->response.Size() == this->counts.Size());
		}

		BinomialResponse::~BinomialResponse()
		{
		}

		int BinomialResponse::NumberOfObservations() const
		{
			return this->response.Size();
		}

		void BinomialResponse::EvaluateWorkingWeightsAndValues(Vector<double> & weights, Vector<double> & values, const Vector<double> & eta) const
		{
			_ASSERT_ARGUMENT(this->response.Size() == weights.Size() &&
				this->response.Size() == values.Size() &&
				this->response.Size() == eta.Size());

			const int nobs = this->response.Size();

			for (int i = 0; i < nobs; ++i)
			{
				const double pi = AntiLogit(eta(i));
				const double mu = this->counts(i) * pi;
				values(i) = this->response(i) - mu; // First derivative in eta
				weights(i) = mu * (1.0 - pi); // Minus the second derivative in eta
			}
		}
	}
}
