#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "WAVEFormat.h"

class WAVEFileWriter {
private:
	std::ofstream file;
	int sampleSize;
public:
	WAVEFileWriter(const std::string&);
	void writeInfo(const WAVEINFO&);
	void writeSamples(std::vector<char>&);
	~WAVEFileWriter();
};
