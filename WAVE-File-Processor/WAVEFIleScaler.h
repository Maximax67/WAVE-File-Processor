#pragma once

#include "WAVEFileReader.h"
#include "WAVEFileWriter.h"
#include "TypedVectorAccessor.h"
#include "dataScaler.h"

class WAVEFileScaler {
private:
	WAVEFileReader* reader = nullptr;
	WAVEFileWriter* writer = nullptr;
	int bufferSize = 0;
	void initReader(const std::string&);
	void initWriter(const std::string&);
public:
	void setBufferSize(const int);
	void scaleFile(const std::string&, const std::string&, const double);
	~WAVEFileScaler();
};
