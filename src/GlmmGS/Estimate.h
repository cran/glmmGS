#ifndef GLMMGS_ESTIMATE_H
#define GLMMGS_ESTIMATE_H

namespace GlmmGS
{
	class Estimate
	{
	private:
		// Fields
		double value;
		double variance;

	public:
		// Construction
		Estimate();
		Estimate(double value, double variance);

		// Properties
		double Value() const;
		double Variance() const;
	};

	// Properties
	inline
	double Estimate::Value() const
	{
		return this->value;
	}

	inline
	double Estimate::Variance() const
	{
		return this->variance;
	}
}

#endif
