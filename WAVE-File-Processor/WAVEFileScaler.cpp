#include "WAVEFIleScaler.h"

void WAVEFileScaler::setBufferSize(const int new_size) {
	if (new_size > 0) {
		bufferSize = new_size;
	}
	else {
		throw std::invalid_argument("Buffer size can't be less than 0!");
	}
}

void WAVEFileScaler::scaleFile(const std::string& input, const std::string& output, const double sr) {
	if (!bufferSize) {
		throw std::exception("Buffer size was not specified");
	}

	initReader(input);

	reader->readInfo();
	WAVEINFO info = reader->getInfo();

	int originalNumSamples = info.dataChunkInfo.Size / (info.fmt.bitsPerSample / 8);
	int interpolatedNumSamples = (int)(originalNumSamples * sr);
	
	info.dataChunkInfo.Size = interpolatedNumSamples * info.fmt.blockAlign;
	info.header.chunkSize = 4 + (8 + sizeof(FMT)) + (8 + sizeof(DATACHUNKINFO) + info.dataChunkInfo.Size);
	
	initWriter(output);
	writer->writeInfo(info);
	
	int cyclesOfInterpolation = (int)ceil(originalNumSamples / bufferSize);
	if (reader->getSampleSize() == 2) {
		dataScaler<int16_t> ds;
		ds.setScaleRatio(sr);
		for (int i = 0; i < cyclesOfInterpolation; i++) {
			std::vector<char> samples = reader->getSamples(bufferSize);
			TypedVectorAccessor<int16_t> accessor(samples);
			std::vector<char> interpolatedSamples = ds.scaleData(accessor);
			writer->writeSamples(interpolatedSamples);
		}
	}
	else {
		dataScaler<uint8_t> ds;
		ds.setScaleRatio(sr);
		for (int i = 0; i < cyclesOfInterpolation; i++) {
			std::vector<char> samples = reader->getSamples(bufferSize);
			TypedVectorAccessor<uint8_t> accessor(samples);
			std::vector<char> interpolatedSamples = ds.scaleData(accessor);
			writer->writeSamples(interpolatedSamples);
		}
	}
}

WAVEFileScaler::~WAVEFileScaler() {
	delete reader;
	delete writer;
}

void WAVEFileScaler::initReader(const std::string& inputfilename) {
	reader = new WAVEFileReader(inputfilename);
	if (reader == nullptr) {
		throw std::exception("Can't allocate memory for WAVEFileReader!");
	}
}

void WAVEFileScaler::initWriter(const std::string& outfilename) {
	writer = new WAVEFileWriter(outfilename);
	if (writer == nullptr) {
		throw std::exception("Can't allocate memory for WAVEFileWriter!");
	}
}
