#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "WAVEFormatValidate.h"

class WAVEFileReader {
private:
	std::string filename;
	std::ifstream file;
	RIFFHEADER header;
	FMT fmt;
	DATACHUNKINFO dataChunkInfo;
	void readInfo();
public:
	WAVEFileReader(const std::string&);
	RIFFHEADER getHeader() const;
	FMT getFMT() const;
	DATACHUNKINFO getDataChunkInfo() const;
	void getNextSample(char*);
	int getSampleSize() const;
	~WAVEFileReader();
};
