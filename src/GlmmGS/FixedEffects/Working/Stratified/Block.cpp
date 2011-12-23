#include "../../../Standard.h"
#include "../../../Variables/IVariable.h"
#include "../../../Estimate.h"
#include "Block.h"

namespace GlmmGS
{
	namespace FixedEffects
	{
		namespace Working
		{
			namespace Stratified
			{
				// Block
				Block::Block(Vector<Pointer<Variables::IVariable> > variables, WeakFactor factor)
					: variables(variables), factor(factor), beta(variables.Size(), factor.NumberOfLevels())
				{
				}

				Block::~Block()
				{
				}

				Vector<Estimate> Block::Coefficients() const
				{
					return this->beta.Estimates();
				}

				// Methods
				void Block::UpdatePredictor(Vector<double> & eta) const
				{
					const int nvars = this->variables.Size();
					for (int j = 0; j < nvars; ++j)
						this->variables(j)->UpdatePredictor(eta, this->beta.Value(j), this->factor);
				}

				int Block::UpdateCoefficients(const Vector<double> & weights, const Vector<double> & values, Comparer comparer)
				{
					const int nvars = this->variables.Size();
					Vector<Vector<double> > jacobian(nvars);
					TriangularMatrix<Vector<double> > precision(nvars);
					for (int j = 0; j < nvars; ++j)
					{
						// Evaluate jacobian (return value optimization)
						Vector<double> ret_jacobian = Variables::ScalarProduct(this->variables(j), values, this->factor);
						Move(jacobian(j), ret_jacobian);
						// Evaluate precision (return value optimization)
						for (int k = 0; k <= j; ++k)
						{
							Vector<double> ret_precision =  Variables::ScalarProduct(this->variables(j), weights, this->variables(k), this->factor);
							Move(precision(j, k), ret_precision);
						}
					}
					// Calculate update
					return this->beta.Update(precision, jacobian, comparer);
				}
			}
		}
	}
}
