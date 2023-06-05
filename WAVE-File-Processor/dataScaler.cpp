#include "dataScaler.h"

template <typename T>
void dataScaler<T>::setScaleRatio(const double sr) {
	if (sr > 0) {
		scaleRatio = sr;
	}
	else {
		throw std::invalid_argument("Scale ratio can't be less than zero");
	}
}

template <typename T>
std::vector<char> dataScaler<T>::scaleData(const TypedVectorAccessor<T>& origSamples) {
	if (scaleRatio == 1 || origSamples.size() == 1) {
		return origSamples.getData();
	}
	
	int interpolatedNumSamples = (int)(origSamples.size() * scaleRatio);
	int interpolateCounter = 0;
	std::vector<char> interpolatedSamples(interpolatedNumSamples * sizeof(T));
	
	T current_sample;
	T next_sample;

	bool wasInterpolation = interpolator.interpolatedBefore();
	if (wasInterpolation) {
		current_sample = interpolator.getLastSample();
	}
	else {
		current_sample = origSamples[0];
	}
	
	for (int i = wasInterpolation ? -1 : 0; i < (int)origSamples.size() - 1; i++) {
		next_sample = origSamples[i + 1];
	
		interpolator.setNewSamples(current_sample, next_sample, wasInterpolation ? i + 1 : i);
	
		double pos_in_orig = interpolateCounter / scaleRatio;
		while (interpolator.newSamplesNeeded(pos_in_orig)) {
			T interpolatedValue = interpolator.getInterpolatedValue(pos_in_orig);
			const char* pointerToValue = (const char*)(&interpolatedValue);
	
			int start_pos = interpolateCounter * sizeof(T);
			for (size_t j = 0; j < sizeof(T); j++) {
				interpolatedSamples[start_pos + j] = pointerToValue[j];
			}
	
			pos_in_orig = ++interpolateCounter / scaleRatio;
		}
	
		current_sample = next_sample;
	}
	
	return interpolatedSamples;
}

template class dataScaler<int16_t>;
template class dataScaler<uint8_t>;
