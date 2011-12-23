#include "../Standard.h"
#include "BinomialResponseSection.h"
#include "../GlmmGSAPI.h"

namespace GlmmGSAPI
{
	namespace Responses
	{
		// BinomialResponseSection
		BinomialResponseSection::BinomialResponseSection(GlmmGSAPI & api)
			: Section(api)
		{
		}

		BinomialResponseSection::~BinomialResponseSection()
		{
		}

		void BinomialResponseSection::AddResponse(WeakVector<const int> values)
		{
			this->values.Reset(new(bl) WeakVector<const int>(values));
		}

		void BinomialResponseSection::AddCounts(WeakVector<const int> counts)
		{
			this->counts.Reset(new(bl) WeakVector<const int>(counts));
		}

		void BinomialResponseSection::EndResponse()
		{
			this->api.response.Reset(new(bl) GlmmGS::Responses::BinomialResponse(*this->values, *this->counts));
		}
	}
}
