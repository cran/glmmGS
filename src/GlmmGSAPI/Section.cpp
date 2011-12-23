#include "Standard.h"
#include "Section.h"
#include "GlmmGSAPI.h"
#include "Responses/BinomialResponseSection.h"
#include "Responses/PoissonResponseSection.h"
#include "FixedEffects/FixedEffectsSection.h"
#include "RandomEffects/RandomEffectsSection.h"

namespace GlmmGSAPI
{
	// Section
	Section::Section(GlmmGSAPI & api) :
		api(api)
	{
	}

	Section::~Section()
	{
	}

	Pointer<Section> Section::BeginResponse(WeakString<const char> family)
	{
		if (family == "binomial")
		{
			typedef Responses::BinomialResponseSection T;
			return Pointer<T>(new(bl) T(this->api));
		}
		else if (family == "poisson")
		{
			typedef Responses::PoissonResponseSection T;
			return Pointer<T>(new(bl) T(this->api));
		}
		else
			throw Exception("Non supported response family");
	}

	void Section::EndResponse()
	{
		throw Exception("Invalid call: EndResponse");
	}

	Pointer<Section> Section::BeginFixedEffects()
	{
		typedef FixedEffects::FixedEffectsSection T;
		return Pointer<T>(new(bl) T(this->api));
	}

	void Section::EndFixedEffects()
	{
		throw Exception("Invalid call: EndFixedEffects");
	}

	Pointer<Section> Section::BeginRandomEffects()
	{
		typedef RandomEffects::RandomEffectsSection T;
		return Pointer<T>(new(bl) T(this->api));
	}

	void Section::EndRandomEffects()
	{
		throw Exception("Invalid call: EndRandomEffects");
	}

	Pointer<Section> Section::BeginBlock()
	{
		throw Exception("Invalid call: BeginBlock");
	}

	void Section::EndBlock()
	{
		throw Exception("Invalid call: EndBlock");
	}

	Pointer<Section> Section::BeginStratifiedBlock(WeakFactor)
	{
		throw Exception("Invalid call: BeginStratifiedBlock");
	}

	void Section::EndStratifiedBlock()
	{
		throw Exception("Invalid call: EndStratifiedBlock");
	}

	void Section::AddResponse(WeakVector<const int>)
	{
		throw Exception("Invalid call: AddResponse");
	}

	void Section::AddCounts(WeakVector<const int>)
	{
		throw Exception("Invalid call: AddCounts");
	}

	void Section::AddOffset(WeakVector<const int> values)
	{
		if (this->api.offset.IsNull() == false)
			throw Exception("Multiple offsets");
		typedef GlmmGS::Offsets::WeakVectorOffset<const int>  T;
		this->api.offset.Reset(new(bl) T(values));
	}

	void Section::AddOffset(WeakVector<const double> values)
	{
		if (this->api.offset.IsNull() == false)
			throw Exception("Multiple offsets");
		typedef GlmmGS::Offsets::WeakVectorOffset<const double>  T;
		this->api.offset.Reset(new(bl) T(values));
	}

	void Section::AddIntercept()
	{
		throw Exception("Invalid call: AddIntercept");
	}

	void Section::AddCovariate(WeakVector<const int>)
	{
		throw Exception("Invalid call: AddCovariate");
	}

	void Section::AddCovariate(WeakVector<const double>)
	{
		throw Exception("Invalid call: AddCovariate");
	}

	void Section::AddIdentityCovarianceModel()
	{
		throw Exception("Invalid call: AddIdentityCovarianceModel");
	}

	void Section::AddPrecisionModel(WeakMatrix<const double>)
	{
		throw Exception("Invalid call: AddPrecisionModel");
	}

	void Section::AddSparsePrecisionModel(const LDL::SparseMatrix<double> &)
	{
		throw Exception("Invalid call: AddSparsePrecisionModel");
	}
}
