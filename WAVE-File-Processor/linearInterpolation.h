#pragma once

#include <cstdint>

template <typename T>
class LinearInterpolation {
private:
	int sample_n = 0;
	T currentSample = 0;
	T nextSample = 0;
public:
	void setNewSamples(const T&, const T&, const int);
	bool newSamplesNeeded(const double) const;
	bool interpolatedBefore() const;
	T getLastSample() const;
	T getInterpolatedValue(const double) const;
};
