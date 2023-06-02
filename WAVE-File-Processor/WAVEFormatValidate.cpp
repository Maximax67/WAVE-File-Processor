#include "WAVEFormatValidate.h"

bool WAVEFormatValidate::validateRIFFHeader(const RIFFHEADER& header) {
	return header.chunkId == 0x46464952 && header.format == 0x45564157;
}

bool WAVEFormatValidate::validateFMT(const FMT& fmt) {
	return fmt.Id == 0x20746D66 && fmt.Size == 16 && fmt.audioFormat == 1;
}

bool WAVEFormatValidate::validateDataChunkInfo(const DATACHUNKINFO& dci) {
	return dci.Id == 0x61746164;
}
