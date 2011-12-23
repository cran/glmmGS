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
					double Square(WeakMatrix<const double> m, const Vector<double> & x)
					{
						_ASSERT_ARGUMENT(m.NumberOfRows() == x.Size() && m.NumberOfColumns() == x.Size());
						const int size = x.Size();
						double sum = 0.0;
						for (int i = 0; i < size; ++i)
						{
							// Diagonal term
							sum += m(i, i) * Math::Square(x(i));

							// Off diagonal terms
							double tmp = 0.0;
							for (int j = 0; j < i; ++j)
								tmp += m(i, j) * x(j);
							sum += 2.0 * x(i) * tmp;
						}
						return sum;
					}

					// Weighted square norm of vector
					double Square(const LDL::SparseMatrix<double> & R, const Vector<double> & x)
					{
						_ASSERT_ARGUMENT(R.NumberOfColumns() == x.Size());
						const int ncols = R.NumberOfColumns();
						double sum = 0.0;
						for (int j = 0; j < ncols; ++j)
						{
							const int p2 = R.Count(j + 1);
							double tmp = 0.0;
							for (int p = R.Count(j); p < p2; ++p)
							{
								const int i = R.Index(p);
								const double value = R.Value(p);
								tmp += x(i) * value;
							}
							sum += x(j) * tmp;
						}
						return sum;
					}

					// Trace of diagonal blocks
					double BlockTrace(int row, int nlevels, const Matrix<double> & a)
					{
						const int offset = row * nlevels;
						double sum = 0.0;
						for (int j = 0; j < nlevels; ++j)
							sum += a(offset + j, offset + j);
						return sum;
					}

					// Trace of diagonal blocks product
					double BlockSquareTrace(int row, int col, int nlevels, const Matrix<double> & a)
					{
						const int offset_row = row * nlevels;
						const int offset_col = col * nlevels;
						const int size = a.NumberOfColumns();
						double sum = 0.0;
						for (int i = 0; i < nlevels; ++i)
							for (int j = 0; j < size; ++j)
								sum += a(offset_row + i, j) * a(j, offset_col + i);
						return sum;
					}


					// Matrix product
					double MatrixProduct(int k, WeakMatrix<const double> m, const Vector<double> & x)
					{
						const int size = m.NumberOfRows();
						double sum = 0.0;
						for (int i = 0; i < size; ++i)
							sum += m(k, i) * x(i);
						return sum;
					}

					// Transposed-matrix product
					double TMatrixProduct(int k, const LDL::SparseMatrix<double> & R, const Vector<double> & x)
					{
						double sum = 0.0;
						const int p2 = R.Count(k + 1);
						for (int p = R.Count(k); p < p2; ++p)
						{
							const int i = R.Index(p);
							const double value = R.Value(p);
							sum += value * x(i);
						}
						return sum;
					}

				}
			}
		}
	}
}
