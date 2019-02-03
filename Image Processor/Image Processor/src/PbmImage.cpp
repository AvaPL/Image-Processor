#include "../inc/PbmImage.h"

PbmImage::PbmImage(const ImageHeader& header, vector<vector<char>> bitmap): Image(header), bitmap(std::move(bitmap))
{
	this->header.format = PBM;
	this->header.maxValue = 1;
}