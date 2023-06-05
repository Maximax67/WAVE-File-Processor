#include "WAVEFileWriter.h"

WAVEFileWriter::WAVEFileWriter(const std::string& filename) {
	sampleSize = 0;

	file.open(filename, std::ios::binary);
	if (!file.is_open()) {
		throw std::exception("Error opening output file!");
	}
}

void WAVEFileWriter::writeInfo(const WAVEINFO& info) {
	sampleSize = info.fmt.bitsPerSample / 8;

	if (!file.write((char*)(&info), sizeof(WAVEINFO))) {
		file.close();
		throw std::exception("Can't write WAVE info headers to output file!");
	}
}

void WAVEFileWriter::writeSamples(std::vector<char>& samples) {
	if (!sampleSize) {
		throw std::exception("WAVEINFO was not written yet! You can't write samples");
	} else if (!file.write(samples.data(), samples.size())) {
		file.close();
		throw std::exception("Can't write sample of data!");
	}
}

WAVEFileWriter::~WAVEFileWriter() {
	file.close();
}
