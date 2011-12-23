#pragma once

extern "C"
{
	// Debug
	void GlmmGSRAPI_SetOutputFile(const char ** buffer);

	// Error
	void GlmmGSRAPI_GetLastError(char ** buffer, const int * size);

	// Sections
	void GlmmGSRAPI_Begin();
	void GlmmGSRAPI_End();
	void GlmmGSRAPI_ForceEnd();
	void GlmmGSRAPI_BeginResponse(const char ** family, const int * length);
	void GlmmGSRAPI_EndResponse();
	void GlmmGSRAPI_BeginFixedEffects();
	void GlmmGSRAPI_EndFixedEffects();
	void GlmmGSRAPI_BeginRandomEffects();
	void GlmmGSRAPI_EndRandomEffects();
	void GlmmGSRAPI_BeginGlobalBlock();
	void GlmmGSRAPI_EndGlobalBlock();
	void GlmmGSRAPI_BeginStratifiedBlock(const int * levels, const int * size);
	void GlmmGSRAPI_EndStratifiedBlock();

	// Variables
	void GlmmGSRAPI_AddResponseInt(const int * values, const int * size);
	void GlmmGSRAPI_AddCountsInt(const int * values, const int * size);
	void GlmmGSRAPI_AddOffsetInt(const int * values, const int * size);
	void GlmmGSRAPI_AddOffsetDbl(const double * values, const int * size);
	void GlmmGSRAPI_AddIntercept();
	void GlmmGSRAPI_AddCovariateInt(const int * values, const int * size);
	void GlmmGSRAPI_AddCovariateDbl(const double * values, const int * size);
	void GlmmGSRAPI_AddCovariatesInt(const int * values, const int * dim);
	void GlmmGSRAPI_AddCovariatesDbl(const double * values, const int * dimensions);

	// Covariance models
	void GlmmGSRAPI_AddIdentityCovarianceModel();
	void GlmmGSRAPI_AddPrecisionModel(const double * values, const int * nrows, const int * ncols);
	void GlmmGSRAPI_AddSparsePrecisionModel(const double * values, const int * indices, const int * counts, const int * ncols);

	// Fit
	void GlmmGSRAPI_Fit(const double * relative_tolerance, const double * absolute_tolerance, const int * maxiter);

	// Results
	void GlmmGSRAPI_GetFixedEffectsSize(int * size);
	void GlmmGSRAPI_GetFixedEffectsEstimates(double * values, const int * size);
	void GlmmGSRAPI_GetFixedEffectsErrors(double * values, const int * size);
	void GlmmGSRAPI_GetRandomEffectsSize(int * size);
	void GlmmGSRAPI_GetRandomEffectsEstimates(double * values, const int * size);
	void GlmmGSRAPI_GetRandomEffectsErrors(double * values, const int * size);
	void GlmmGSRAPI_GetCovarianceComponentsSize(int * size);
	void GlmmGSRAPI_GetCovarianceComponentsEstimates(double * values, const int * size);
	void GlmmGSRAPI_GetCovarianceComponentsErrors(double * values, const int * size);
	void GlmmGSRAPI_GetIterations(int * iterations);
}
