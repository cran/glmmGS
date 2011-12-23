#include "GlmmGSRAPI.h"
#include "GlmmGSAPI/GlmmGSAPI.h"
#include "GlmmGS/Controls.h"
#include "Utilities/Exceptions/Exception.h"

using namespace GlmmGSAPI;

void GlmmGSRAPI_SetOutputFile(const char ** buffer)
{
	const char * filename = *buffer;
	if (Utilities::IO::stream != stdout)
		fclose(Utilities::IO::stream);
	Utilities::IO::stream = fopen(filename, "wt");
}

void GlmmGSRAPI_GetLastError(char ** buffer, const int * size)
{
	if (*buffer != NULL && *size > 0)
		the_api.GetLastError(*buffer, *size);
}

void GlmmGSRAPI_Begin()
{
	try
	{
		the_api.Begin();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_End()
{
	try
	{
		the_api.End();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_ForceEnd()
{
	// No exceptions should be thrown here
	the_api.ForceEnd();
}

void GlmmGSRAPI_BeginResponse(const char ** family, const int * length)
{
	try
	{
		the_api.BeginResponse(WeakString<const char>(*family, *length));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_EndResponse()
{
	try
	{
		the_api.EndResponse();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_BeginFixedEffects()
{
	try
	{
		the_api.BeginFixedEffects();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_EndFixedEffects()
{
	try
	{
		the_api.EndFixedEffects();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_BeginRandomEffects()
{
	try
	{
		the_api.BeginRandomEffects();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_EndRandomEffects()
{
	try
	{
		the_api.EndRandomEffects();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_BeginGlobalBlock()
{
	try
	{
		the_api.BeginGlobalBlock();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_EndGlobalBlock()
{
	try
	{
		the_api.EndGlobalBlock();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_BeginStratifiedBlock(const int * levels, const int * size)
{
	try
	{
		the_api.BeginStratifiedBlock(WeakFactor(levels, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_EndStratifiedBlock()
{
	try
	{
		the_api.EndStratifiedBlock();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddResponseInt(const int * values, const int * size)
{
	try
	{
		the_api.AddResponse(WeakVector<const int>(values, * size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddCountsInt(const int * values, const int * size)
{
	try
	{
		the_api.AddCounts(WeakVector<const int>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

template <class TYPE>
void GlmmGSRAPI_AddOffsetImpl(const TYPE * values, const int * size)
{
	try
	{
		the_api.AddOffset(WeakVector<const TYPE>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddOffsetInt(const int * values, const int * size)
{
	GlmmGSRAPI_AddOffsetImpl(values, size);
}

void GlmmGSRAPI_AddOffsetDbl(const double * values, const int * size)
{
	GlmmGSRAPI_AddOffsetImpl(values, size);
}

void GlmmGSRAPI_AddIntercept()
{
	try
	{
		the_api.AddIntercept();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

template <class TYPE>
void GlmmGSRAPI_AddCovariateImpl(const TYPE * values, const int * size)
{
	try
	{
		the_api.AddCovariate(WeakVector<const TYPE>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddCovariateInt(const int * values, const int * size)
{
	GlmmGSRAPI_AddCovariateImpl(values, size);
}

void GlmmGSRAPI_AddCovariateDbl(const double * values, const int * size)
{
	GlmmGSRAPI_AddCovariateImpl(values, size);
}

template <class TYPE>
void GlmmGSRAPI_AddCovariatesImpl(const TYPE * values, const int * dimensions)
{
	try
	{
		const int nrows = dimensions[0];
		const int ncols = dimensions[1];
		for (int j = 0; j < ncols; ++j)
			the_api.AddCovariate(WeakVector<const TYPE>(values + j * nrows, nrows));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddCovariatesInt(const int * values, const int * dimensions)
{
	GlmmGSRAPI_AddCovariatesImpl(values, dimensions);
}

void GlmmGSRAPI_AddCovariatesDbl(const double * values, const int * dimensions)
{
	GlmmGSRAPI_AddCovariatesImpl(values, dimensions);
}

void GlmmGSRAPI_AddIdentityCovarianceModel()
{
	try
	{
		the_api.AddIdentityCovarianceModel();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddPrecisionModel(const double * values, const int * nrows, const int * ncols)
{
	try
	{
		if (*nrows != *ncols)
			throw Utilities::Exceptions::Exception("Precision matrix must be square");
		// TODO: check matrix is symmetric
		the_api.AddPrecisionModel(WeakMatrix<const double>(values, *nrows, *ncols));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_AddSparsePrecisionModel(const double * values, const int * indices, const int * counts, const int * ncols)
{
	try
	{
		// Counters
		const int n = *ncols; // Number of columns
		const int nz = counts[n]; // Total number of non-zero elements

		// It is safe to use const_cast since we embed the const pointers inside constant objects
		const NewTypes::Vector<double> vvalues(NewTypes::External<double>(const_cast<double *>(values)), nz);
		const NewTypes::Vector<int> vindices(NewTypes::External<int>(const_cast<int *>(indices)), nz);
		const NewTypes::Vector<int> vcounts(NewTypes::External<int>(const_cast<int *>(counts)), n + 1);

		// Sparse matrix
		const LDL::SparseMatrix<double> R(vvalues, vindices, vcounts);

		the_api.AddSparsePrecisionModel(R);
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_Fit(const double * relative_tolerance, const double * absolute_tolerance, const int * maxiter)
{
	try
	{
		GlmmGS::Controls controls(*relative_tolerance, *absolute_tolerance, *maxiter);
		the_api.Fit(controls);
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetFixedEffectsSize(int * size)
{
	try
	{
		*size = the_api.GetFixedEffectsSize();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetFixedEffectsEstimates(double * values, const int * size)
{
	try
	{
		the_api.GetFixedEffectsEstimates(WeakVector<double>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetFixedEffectsErrors(double * values, const int * size)
{
	try
	{
		the_api.GetFixedEffectsErrors(WeakVector<double>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetRandomEffectsSize(int * size)
{
	try
	{
		*size = the_api.GetRandomEffectsSize();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetRandomEffectsEstimates(double * values, const int * size)
{
	try
	{
		the_api.GetRandomEffectsEstimates(WeakVector<double>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetRandomEffectsErrors(double * values, const int * size)
{
	try
	{
		the_api.GetRandomEffectsErrors(WeakVector<double>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetCovarianceComponentsSize(int * size)
{
	try
	{
		*size = the_api.GetCovarianceComponentsSize();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetCovarianceComponentsEstimates(double * values, const int * size)
{
	try
	{
		the_api.GetCovarianceComponentsEstimates(WeakVector<double>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetCovarianceComponentsErrors(double * values, const int * size)
{
	try
	{
		the_api.GetCovarianceComponentsErrors(WeakVector<double>(values, *size));
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}

void GlmmGSRAPI_GetIterations(int * iterations)
{
	try
	{
		*iterations = the_api.GetIterations();
	}
	catch (Exception & e)
	{
		the_api.SetLastError(e);
	}
}
