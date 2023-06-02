#include "WAVEFileWriter.h"

WAVEFileWriter::WAVEFileWriter(const std::string& filename, const RIFFHEADER& h, const FMT& f, const DATACHUNKINFO& d) {
	sampleSize = f.bitsPerSample / 8;

	file.open(filename, std::ios::binary);
	if (!file.is_open()) {
		throw std::exception("Error opening output file!");
	}

	writeInfo(h, f, d);
}

void WAVEFileWriter::writeInfo(const RIFFHEADER& h, const FMT& f, const DATACHUNKINFO& d) {
	if (!file.write((char*)(&h), sizeof(RIFFHEADER))) {
		throw std::exception("Can't write riff header to output file!");
	}
	if (!file.write((char*)(&f), sizeof(FMT))) {
		throw std::exception("Can't write fmt to output file!");
	}
	if (!file.write((char*)(&d), sizeof(DATACHUNKINFO))) {
		throw std::exception("Can't write data chunk info to output file!");
	}
}

void WAVEFileWriter::writeNextSample(const char* sample) {
	if (!file.write(sample, sampleSize)) {
		throw std::exception("Can't write sample of data!");
	}
}

WAVEFileWriter::~WAVEFileWriter() {
	file.close();
}
