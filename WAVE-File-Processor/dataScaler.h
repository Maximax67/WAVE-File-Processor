#pragma once

#include "WAVEFormat.h"
#include "WAVEFileReader.h"
#include "WAVEFileWriter.h"
#include "linearInterpolation.h"

template <typename T>
class dataScaler {
private:
	LinearInterpolation<T> interpolator;
	WAVEFileReader* reader;
	WAVEFileWriter* writer;
	const double scaleRatio;
	const int originalNumSamples;
	const int interpolatedNumSamples;
public:
	dataScaler(WAVEFileReader*, WAVEFileWriter*, const int, const int, const double);
	void scaleData();
};
