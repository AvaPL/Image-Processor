#include "../inc/Image.h"
#include "../inc/DefaultValues.h"

Image::~Image() = default;

ImageHeader Image::GetPbmHeader() const
{
	ImageHeader newHeader = header;
	newHeader.format = PBM;
	newHeader.maxValue = PBM_DEFAULT_MAX_VALUE;
	return newHeader;
}

ImageHeader Image::GetPgmHeader(const unsigned short maxGrayValue) const
{
	ImageHeader newHeader = header;
	newHeader.format = PGM;
	newHeader.maxValue = maxGrayValue;
	return newHeader;
}

ImageHeader Image::GetPpmHeader(const unsigned short maxColorValue) const
{
	ImageHeader newHeader = header;
	newHeader.format = PPM;
	newHeader.maxValue = maxColorValue;
	return newHeader;
}
