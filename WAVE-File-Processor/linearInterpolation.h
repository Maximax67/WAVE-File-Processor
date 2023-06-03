#pragma once

#include <cstdint>

template <typename T>
class LinearInterpolation {
private:
	int sample_n;
	T currentSample;
	T nextSample;
public:
	void setNewSamples(const T&, const T&, const int);
	bool newSamplesNeeded(const double) const;
	T getInterpolatedValue(const double) const;
};
