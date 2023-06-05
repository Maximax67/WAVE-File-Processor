#include "utils.h"
#include "WAVEFileScaler.h"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: [program name].exe input.wav output.wav scaleRatio" << std::endl;
        return 0;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    double scaleRatio = 0;

    if (!utils::convertToDouble(argv[3], &scaleRatio)) {
        std::cout << "Error! " << argv[3] << " is not a double number!" << std::endl;
    }

    if (scaleRatio < 0.001 || scaleRatio > 1000) {
        std::cout << "Error! Scale ratio must be greater than 0.001 and less than 1000!" << std::endl;
        scaleRatio = 0;
    }

    if (utils::validateInputOutputFiles(inputFile, outputFile) && scaleRatio) {
        try {
            WAVEFileScaler scaler;
            scaler.setBufferSize(utils::defaultBufferSize);
            scaler.scaleFile(inputFile, outputFile, scaleRatio);
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}
