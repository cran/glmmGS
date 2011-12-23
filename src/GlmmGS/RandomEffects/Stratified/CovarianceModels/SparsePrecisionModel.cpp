#include "../../../Standard.h"
#include "../../Working/Stratified/CovarianceModels/ICovarianceModel.h"
#include "../../Working/Stratified/CovarianceModels/SparsePrecisionModel.h"
#include "SparsePrecisionModel.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Stratified
		{
			namespace CovarianceModels
			{
				// Construction
				SparsePrecisionModel::SparsePrecisionModel(int nvars, const LDL::SparseMatrix<double> precision)
					: nvars(nvars), precision(precision)
				{
				}

				SparsePrecisionModel::~SparsePrecisionModel()
				{
				}

				// Implementation
				Pointer<Working::Stratified::CovarianceModels::ICovarianceModel> SparsePrecisionModel::CreateWorking() const
				{
					typedef Working::Stratified::CovarianceModels::SparsePrecisionModel T;
					return Pointer<T>(new(bl) T(this->nvars, this->precision));
				}
			}
		}
	}
}
