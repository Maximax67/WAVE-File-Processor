#pragma once

#include <iostream>
#include <string>

namespace utils {
	const std::string waveExtension = "wav";
	bool validatePath(const std::string&);
	bool validateExtension(const std::string&, const std::string&);
	bool convertToDouble(const char*, double*);
	bool validateInputOutputFiles(const std::string&, const std::string&);
};
