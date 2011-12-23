#pragma once

// Utilities
#include "../Utilities/Utilities.h"
#include "../Utilities/Exceptions/Exceptions.h"
#include "../Utilities/IO/IO.h"

// Types
#include "../GlmmGS/Controls.h"
#include "../GlmmGS/Estimate.h"

// Response
#include "../GlmmGS/Responses/IResponse.h"
#include "../GlmmGS/Responses/BinomialResponse.h"
#include "../GlmmGS/Responses/PoissonResponse.h"

// Offsets
#include "../GlmmGS/Offsets/IOffset.h"
#include "../GlmmGS/Offsets/ZeroOffset.h"
#include "../GlmmGS/Offsets/WeakVectorOffset.h"

// Fixed effects
#include "../GlmmGS/FixedEffects/IBlock.h"
#include "../GlmmGS/FixedEffects/Global/Block.h"
#include "../GlmmGS/FixedEffects/Stratified/Block.h"

// Random effects
#include "../GlmmGS/RandomEffects/IBlock.h"
#include "../GlmmGS/RandomEffects/Global/Block.h"
#include "../GlmmGS/RandomEffects/Stratified/Block.h"

// Covariance models
#include "../GlmmGS/RandomEffects/Global/CovarianceModels/ICovarianceModel.h"
#include "../GlmmGS/RandomEffects/Global/CovarianceModels/IdentityModel.h"
#include "../GlmmGS/RandomEffects/Global/CovarianceModels/PrecisionModel.h"
#include "../GlmmGS/RandomEffects/Stratified/CovarianceModels/ICovarianceModel.h"
#include "../GlmmGS/RandomEffects/Stratified/CovarianceModels/IdentityModel.h"
#include "../GlmmGS/RandomEffects/Stratified/CovarianceModels/PrecisionModel.h"
#include "../GlmmGS/RandomEffects/Stratified/CovarianceModels/SparsePrecisionModel.h"

// Boosters
#include "../GlmmGS/RandomEffects/Working/Stratified/Boosters/IBooster.h"
#include "../GlmmGS/RandomEffects/Working/Stratified/Boosters/Default.h"
#include "../GlmmGS/RandomEffects/Working/Stratified/Boosters/RemoveMean.h"

// Variables
#include "../GlmmGS/Variables/IVariable.h"
#include "../GlmmGS/Variables/Intercept.h"
#include "../GlmmGS/Variables/WeakVectorVariable.h"

// GlmmGS
#include "../GlmmGS/GlmmGS.h"

namespace GlmmGSAPI
{
	using namespace Utilities;
	using namespace Utilities::Exceptions;
	using namespace Utilities::IO;
}
