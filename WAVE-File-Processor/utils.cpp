#include "utils.h"

bool utils::validatePath(const std::string& path) {
	struct stat sb;
	return stat(path.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR);
}

bool utils::validateExtension(const std::string& filename, const std::string& extension) {
	return filename.substr(filename.find_last_of('.') + 1) == extension;
}

bool utils::convertToDouble(const char* line, double* number) {
	double n = atof(line);
	if (n != 0 || (n == 0 && line == "0")) {
		*number = n;
		return true;
	}

	return false;
}

bool utils::validateInputOutputFiles(const std::string& inputFile, const std::string& outputFile) {
    bool was_error = false;
    if (!utils::validateExtension(inputFile, waveExtension)) {
        std::cout << "Invalid extension for input file: " << inputFile << std::endl;
        was_error = true;
    }
    if (!utils::validatePath(inputFile)) {
        std::cout << "Invalid path for input file: " << inputFile << std::endl;
        was_error = true;
    }
    if (!utils::validateExtension(outputFile, waveExtension)) {
        std::cout << "Invalid extension for output file: " << outputFile << std::endl;
        was_error = true;
    }

    return !was_error;
}
