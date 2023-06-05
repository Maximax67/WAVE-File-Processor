#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "WAVEFormatValidate.h"

class WAVEFileReader {
private:
	std::ifstream file;
	WAVEINFO info;
	int readedSamples = 0;
	void readInfo();
	int notReadedSamples() const;
public:
	WAVEFileReader(const std::string&);
	int getSampleSize() const;
	WAVEINFO getInfo() const;
	std::vector<char> getSamples(const int);
	~WAVEFileReader();
};
