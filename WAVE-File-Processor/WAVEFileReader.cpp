#include "WAVEFileReader.h"

WAVEFileReader::WAVEFileReader(const std::string& filename) {
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::exception("Error opening input file!");
    }
}

WAVEFileReader::~WAVEFileReader() {
    file.close();
}

void WAVEFileReader::readInfo() {
    char* headerPtr = (char*)(&info.header);
    char* subch1Ptr = (char*)(&info.fmt);
    char* subch2Ptr = (char*)(&info.dataChunkInfo);

    if (!file.read(headerPtr, sizeof(RIFFHEADER))) {
        throw std::exception("Error reading header");
    }

    if (!WAVEFormatValidate::validateRIFFHeader(info.header)) {
        throw std::exception("Invalid RIFF Header");
    }

    if (!file.read(subch1Ptr, sizeof(FMT))) {
        throw std::exception("Error reading FMT");
    }

    if (!WAVEFormatValidate::validateFMT(info.fmt)) {
        throw std::exception("Invalid FMT chunk");
    }

    if (!file.read(subch2Ptr, sizeof(DATACHUNKINFO))) {
        throw std::exception("Error reading data chunk info");
    }

    if (!WAVEFormatValidate::validateDataChunkInfo(info.dataChunkInfo)) {
        throw std::exception("Invalid Data chunk");
    }
}

int WAVEFileReader::notReadedSamples() const {
    return info.dataChunkInfo.Size / (info.fmt.bitsPerSample / 8) - readedSamples;
}

int WAVEFileReader::getSampleSize() const {
    return info.fmt.bitsPerSample / 8;
}

std::vector<char> WAVEFileReader::getSamples(const int bufferSize) {
    int toRead = bufferSize;
    int notReaded = notReadedSamples();

    if (notReaded < toRead) {
        toRead = notReaded;
    }

    int toReadSize = toRead * getSampleSize();

    std::vector<char> samples(toReadSize);
    if (!file.read(samples.data(), toReadSize)) {
        throw std::exception("Can't read sample of data!");
    }

    readedSamples += toRead;

    return samples;
}

WAVEINFO WAVEFileReader::getInfo() const {
    return info;
}
