#pragma once

#include <string>
#include <fstream>

#include "WAVEFormat.h"

class WAVEFileWriter {
private:
	std::string filename;
	std::ofstream file;
	int sampleSize;
	void writeInfo(const RIFFHEADER&, const FMT&, const DATACHUNKINFO&);
public:
	WAVEFileWriter(const std::string&, const RIFFHEADER&, const FMT&, const DATACHUNKINFO&);
	void writeNextSample(const char*);
	~WAVEFileWriter();
};
