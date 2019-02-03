#include "../inc/PgmImage.h"

PgmImage::PgmImage(const ImageHeader& header, vector<vector<unsigned short>> graymap): Image(header),
                                                                                       graymap(std::move(graymap))
{
	this->header.format = PGM;
}