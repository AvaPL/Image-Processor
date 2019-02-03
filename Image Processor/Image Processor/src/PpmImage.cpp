#include "../inc/PpmImage.h"

PpmImage::PpmImage(const ImageHeader& header, vector<vector<RgbPixel>> colormap) : Image(header),
                                                                                   colormap(std::move(colormap))
{
	this->header.format = PPM;
}