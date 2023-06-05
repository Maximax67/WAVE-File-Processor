#include "linearInterpolation.h"

template <typename T>
void LinearInterpolation<T>::setNewSamples(const T& s1, const T& s2, const int n) {
	currentSample = s1;
	nextSample = s2;
	sample_n = n;
}

template <typename T>
bool LinearInterpolation<T>::newSamplesNeeded(const double val) const {
	return val < sample_n + 1;
}

template <typename T>
bool LinearInterpolation<T>::interpolatedBefore() const {
	return sample_n != 0;
}

template <typename T>
T LinearInterpolation<T>::getLastSample() const {
	return nextSample;
}

template <typename T>
T LinearInterpolation<T>::getInterpolatedValue(const double val) const {
	return (T)(currentSample * (1 - (val - sample_n)) + nextSample * (val - sample_n));
}

template class LinearInterpolation<int16_t>;
template class LinearInterpolation<uint8_t>;
