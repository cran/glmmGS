#pragma once

#include "../../Utilities/Exceptions/Exception.h"

namespace GlmmGSAPI
{
	namespace Exceptions
	{
		// InvalidSize
		class InvalidSizeException : public Exception
		{
		public:
			// Construction
			InvalidSizeException() : Exception("Invalid size")
			{
			}
		};
		
		// MultipleCovarianceModels
		class MultipleCovarianceModelsException : public Exception
		{
		public:
			// Construction
			MultipleCovarianceModelsException() : Exception("Only one covariance model per block can be specified")
			{
			}
		};
		
		// NoCovarianceModel
		class NoCovarianceModelException : public Exception
		{
		public:
			// Construction
			NoCovarianceModelException () : Exception("Covariance model was not specified")
			{
			}
		};

		// NoVariableAfterCovarianceModelException
		class NoVariableAfterCovarianceModelException : public Exception
		{
		public:
			// Construction
			NoVariableAfterCovarianceModelException () : Exception("Covariance model must be added last")
			{
			}
		};
	}
}
