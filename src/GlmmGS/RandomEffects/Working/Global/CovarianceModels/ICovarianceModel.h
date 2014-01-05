#ifndef GLMMGS_RANDOMEFFECTS_WORKING_COVARIANCEMODEL_ICOVARIANCEMODEL_H
#define GLMMGS_RANDOMEFFECTS_WORKING_COVARIANCEMODEL_ICOVARIANCEMODEL_H

#include "../../../../Standard.h"
#include "../../../../Estimate.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Global
			{
				namespace CovarianceModels
				{
					// CovarianceModel
					class ICovarianceModel
					{
					protected:
						// Fields
						Vector<double> theta;
					private:
						CholeskyDecomposition chol;

					protected:
						// Implementation
						int Update(const TriangularMatrix<double> & minus_hessian,
								const Vector<double> & jacobian, Comparer comparer);
					public:
						// Construction
						ICovarianceModel(int npars);
						virtual ~ICovarianceModel();

						// Properties
						virtual Vector<double> CoefficientsVariance() const = 0;
						Vector<Estimate> Estimates() const;

						// Methods
						virtual void Decompose(const TriangularMatrix<double> & precision) = 0;
						virtual int Update(const Vector<double> & beta, Comparer comparer) = 0;
						virtual Vector<double> CoefficientsUpdate(const Vector<double> & jacobian, const Vector<double> & beta) const = 0;
					};
				}
			}
		}
	}
}

#endif
