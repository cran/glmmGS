#ifndef GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_COVARIANCEMODELS_FUNCTIONS_H
#define GLMMGS_RANDOMEFFECTS_WORKING_STRATIFIED_COVARIANCEMODELS_FUNCTIONS_H

#include "../../../../Standard.h"

namespace GlmmGS
{
	namespace RandomEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				namespace CovarianceModels
				{
					// Weighted square norm of vector
					double Square(WeakMatrix<const double> m, const Vector<double> & x);
					double Square(const LDL::SparseMatrix<double> & R, const Vector<double> & x);

					// Trace of diagonal blocks
					double BlockTrace(int row, int nlevels, const Matrix<double> & a);

					// Trace of diagonal blocks product
					double BlockSquareTrace(int row, int col, int nlevels, const Matrix<double> & a);

					// Matrix product
					double MatrixProduct(int k, WeakMatrix<const double> m, const Vector<double> & x);

					// Transposed-matrix product
					double TMatrixProduct(int k, const LDL::SparseMatrix<double> & R, const Vector<double> & x);
				}
			}
		}
	}
}

#endif
