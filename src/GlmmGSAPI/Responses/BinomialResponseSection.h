#ifndef RESPONSES_GLMMGSAPI_RESPONSES_BINOMIALRESPONSESECTION_H
#define RESPONSES_GLMMGSAPI_RESPONSES_BINOMIALRESPONSESECTION_H

#include "../Standard.h"
#include "../Section.h"

namespace GlmmGSAPI
{
	namespace Responses
	{
		// BinomialResponseSection
		class BinomialResponseSection : public Section
		{
		private:
			// Fields
			Pointer<WeakVector<const int> > values;
			Pointer<WeakVector<const int> > counts;

			// Implementation
			void AddResponse(WeakVector<const int> values);
			void AddCounts(WeakVector<const int> values);
			void EndResponse();

		public:
			// Construction
			BinomialResponseSection(GlmmGSAPI & api);
			~BinomialResponseSection();
		};
	}
}

#endif
