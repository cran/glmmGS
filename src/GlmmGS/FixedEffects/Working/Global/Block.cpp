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
			namespace Global
			{
				// Block
				Block::Block(Vector<Pointer<Variables::IVariable> > variables)
					: variables(variables), beta(variables.Size())
				{
				}

				Block::~Block()
				{
				}

				// Properties
				Vector<Estimate> Block::Coefficients() const
				{
					return this->beta.Estimates();
				}

				// Methods
				void Block::UpdatePredictor(Vector<double> & eta) const
				{
					const int nvars = this->variables.Size();
					for (int j = 0; j < nvars; ++j)
						this->variables(j)->UpdatePredictor(eta, this->beta.Value(j));
				}

				int Block::UpdateCoefficients(const Vector<double> & weights, const Vector<double> & values, Comparer comparer)
				{
					const int nvars = this->variables.Size();
					Vector<double> jacobian(nvars);
					TriangularMatrix<double> precision(nvars);
					for (int j = 0; j < nvars; ++j)
					{
						// Evaluate jacobian
						jacobian(j) = Variables::ScalarProduct(this->variables(j), values);
						// Evaluate precision
						for (int k = 0; k <= j; ++k)
							precision(j, k) = Variables::ScalarProduct(this->variables(j), weights, this->variables(k));
					}
					// Calculate update
					return this->beta.Update(precision, jacobian, comparer);
				}
			}
		}
	}
}
