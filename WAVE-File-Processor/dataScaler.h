#pragma once

#include <stdexcept>

#include "WAVEFormat.h"
#include "linearInterpolation.h"
#include "TypedVectorAccessor.h"

template <typename T>
class dataScaler {
private:
	LinearInterpolation<T> interpolator;
	double scaleRatio = 1;
public:
	void setScaleRatio(const double);
	std::vector<char> scaleData(const TypedVectorAccessor<T>&);
};
