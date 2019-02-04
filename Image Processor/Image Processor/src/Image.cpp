#include "../inc/Image.h"
#include "../inc/FormatConvertingConstants.h"

// Image::~Image() = default;

ImageHeader Image::GetPbmHeader() const
{
	ImageHeader newHeader = header;
	newHeader.format = PBM;
	newHeader.maxValue = PBM_MAX_VALUE;
	return newHeader;
}

ImageHeader Image::GetPgmHeader() const
{
	ImageHeader newHeader = header;
	newHeader.format = PGM;
	newHeader.maxValue = PGM_MAX_GRAY_VALUE;
	return newHeader;
}

ImageHeader Image::GetPpmHeader() const
{
	ImageHeader newHeader = header;
	newHeader.format = PPM;
	newHeader.maxValue = PPM_MAX_COLOR_VALUE;
	return newHeader;
}
