#include "WAVEFileReader.h"

WAVEFileReader::WAVEFileReader(const std::string& filename) {
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::exception("Error opening input file!");
    }

    readInfo();
}

WAVEFileReader::~WAVEFileReader() {
    file.close();
}

void WAVEFileReader::readInfo() {
    char* headerPtr = (char*)(&header);
    char* subch1Ptr = (char*)(&fmt);
    char* subch2Ptr = (char*)(&dataChunkInfo);

    if (!file.read(headerPtr, sizeof(RIFFHEADER))) {
        throw std::exception("Error reading header");
    }

    if (!file.read(subch1Ptr, sizeof(FMT))) {
        throw std::exception("Error reading FMT");
    }

    if (!file.read(subch2Ptr, sizeof(DATACHUNKINFO))) {
        throw std::exception("Error reading data chunk info");
    }
}

int WAVEFileReader::getSampleSize() const {
    return fmt.bitsPerSample / 8;
}

void WAVEFileReader::getNextSample(char* sample) {
    if (!file.read(sample, getSampleSize())) {
        throw std::exception("Can't read sample of data!");
    }
}

RIFFHEADER WAVEFileReader::getHeader() const {
    return header;
}

FMT WAVEFileReader::getFMT() const {
    return fmt;
}

DATACHUNKINFO WAVEFileReader::getDataChunkInfo() const {
    return dataChunkInfo;
}
