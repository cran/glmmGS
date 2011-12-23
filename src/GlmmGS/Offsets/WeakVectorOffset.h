#pragma once

#include "../Standard.h"
#include "IOffset.h"
namespace GlmmGS
{
	namespace Offsets
	{
		// WeakVectorOffset
		template <class TYPE>
		class WeakVectorOffset : public IOffset
		{
		private:
			WeakVector<TYPE> values;

		public:
			// Construction
			WeakVectorOffset(WeakVector<TYPE> values);
			~WeakVectorOffset();

			// Methods
			void InitializePredictor(Vector<double> & eta) const;
		};

		// Construction
		template <class TYPE>
		WeakVectorOffset<TYPE>::WeakVectorOffset(WeakVector<TYPE> values)
			: values(values)
		{
		}

		template <class TYPE>
		WeakVectorOffset<TYPE>::~WeakVectorOffset()
		{
		}

		// Methods
		template <class TYPE>
		void WeakVectorOffset<TYPE>::InitializePredictor(Vector<double> & eta) const
		{
			_ASSERT_ARGUMENT(eta.Size() == this->values.Size());
			for (int i = 0; i < this->values.Size(); ++i)
				eta(i) = this->values(i);
		};
	}
}
