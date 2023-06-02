#include "dataScaler.h"

template <typename T>
dataScaler<T>::dataScaler(WAVEFileReader* r, WAVEFileWriter* w, const int os, const int is, const double sr) :
	scaleRatio(sr), originalNumSamples(os), interpolatedNumSamples(is), interpolator() {
	reader = r;
	writer = w;
}

template <typename T>
void dataScaler<T>::scaleData() {
	T current_sample, next_sample;

	int interpolateCounter = 0;
	T interpolateValue;

	char* cur_p = (char*)(&current_sample);
	char* next_p = (char*)(&next_sample);
	char* value_p = (char*)(&interpolateValue);

	reader->getNextSample(cur_p);

	for (int i = 0; i < originalNumSamples - 1; i++) {
		reader->getNextSample(next_p);

		interpolator.setNewSamples(current_sample, next_sample, i);

		double pos_in_orig = interpolateCounter / scaleRatio;
		while (interpolator.newSamplesNeeded(pos_in_orig)) {
			interpolateValue = interpolator.getInterpolatedValue(pos_in_orig);
			writer->writeNextSample((char*)value_p);
			pos_in_orig = ++interpolateCounter / scaleRatio;
		}

		current_sample = next_sample;
	}
}

template class dataScaler<int16_t>;
template class dataScaler<uint8_t>;
