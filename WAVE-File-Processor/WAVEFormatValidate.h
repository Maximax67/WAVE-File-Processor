#pragma once

#include "WAVEFormat.h"

namespace WAVEFormatValidate {
	bool validateRIFFHeader(const RIFFHEADER&);
	bool validateFMT(const FMT&);
	bool validateDataChunkInfo(const DATACHUNKINFO&);
};
