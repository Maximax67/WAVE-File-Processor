#include "WAVEFIleScaler.h"

WAVEFileScaler::WAVEFileScaler(const std::string& input, const std::string& output, const double sr) {	
	initReader(input);

	RIFFHEADER header = reader->getHeader();
	FMT fmt = reader->getFMT();
	DATACHUNKINFO dci = reader->getDataChunkInfo();

	int originalNumSamples = dci.Size / fmt.blockAlign;
	int interpolatedNumSamples = (int)(originalNumSamples * sr);

	dci.Size = interpolatedNumSamples * fmt.blockAlign;
	header.chunkSize = 4 + (8 + sizeof(fmt)) + (8 + sizeof(DATACHUNKINFO) + dci.Size);
	
	initWriter(output, header, fmt, dci);

	if (reader->getSampleSize() == 2) {
		dataScaler<int16_t> ds(reader, writer, originalNumSamples, interpolatedNumSamples, sr);
		ds.scaleData();
	}
	else {
		dataScaler<uint8_t> ds(reader, writer, originalNumSamples, interpolatedNumSamples, sr);
		ds.scaleData();
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

void WAVEFileScaler::initWriter(const std::string& outfilename, const RIFFHEADER& header, const FMT& fmt, const DATACHUNKINFO& dci) {
	writer = new WAVEFileWriter(outfilename, header, fmt, dci);
	if (writer == nullptr) {
		throw std::exception("Can't allocate memory for WAVEFileWriter!");
	}
}
