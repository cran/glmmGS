#pragma once

#include "Standard.h"

namespace GlmmGSAPI
{
	// Forward declaration
	class GlmmGSAPI;

	// Section
	class Section
	{
	// Disable assignment operator
	const Section & operator =(const Section &);

	protected:
		// Fields
		GlmmGSAPI & api;

	public:
		// Construction
		Section(GlmmGSAPI & api);
		virtual ~Section();
		
		// Methods
		virtual Pointer<Section> BeginResponse(WeakString<const char> family);
		virtual void EndResponse();
		virtual Pointer<Section> BeginFixedEffects();
		virtual void EndFixedEffects();
		virtual Pointer<Section> BeginRandomEffects();
		virtual void EndRandomEffects();
		virtual Pointer<Section> BeginBlock();
		virtual void EndBlock();
		virtual Pointer<Section> BeginStratifiedBlock(WeakFactor factor);
		virtual void EndStratifiedBlock();
		virtual void AddResponse(WeakVector<const int> values);
		virtual void AddCounts(WeakVector<const int> values);
		virtual void AddOffset(WeakVector<const int> values);
		virtual void AddOffset(WeakVector<const double> values);
		virtual void AddIntercept();
		virtual void AddCovariate(WeakVector<const int> values);
		virtual void AddCovariate(WeakVector<const double> values);
		virtual void AddIdentityCovarianceModel();
		virtual void AddPrecisionModel(WeakMatrix<const double> precision);
		virtual void AddSparsePrecisionModel(const LDL::SparseMatrix<double> & precision);
	};
}
