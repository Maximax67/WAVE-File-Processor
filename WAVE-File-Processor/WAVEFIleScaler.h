#pragma once

#include "dataScaler.h"

class WAVEFileScaler {
private:
	WAVEFileReader* reader = nullptr;
	WAVEFileWriter* writer = nullptr;
	void initReader(const std::string&);
	void initWriter(const std::string&, const RIFFHEADER&, const FMT&, const DATACHUNKINFO&);
public:
	WAVEFileScaler(const std::string&, const std::string&, const double);
	~WAVEFileScaler();
};
