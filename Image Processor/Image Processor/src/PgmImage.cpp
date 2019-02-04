#include "../inc/PgmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PgmImage::PgmImage(const ImageHeader& header, vector<vector<GrayPixel>> graymap): Image(header),
                                                                                  graymap(std::move(graymap))
{
	this->header.format = PGM;
}

shared_ptr<Image> PgmImage::ToPbm()
{
	ImageHeader newHeader = GetPbmHeader();
	auto newBitmap = GraymapToBitmap();
	return make_shared<PbmImage>(newHeader, newBitmap);
}

vector<vector<BitPixel>> PgmImage::GraymapToBitmap()
{
	auto bitmap = vector<vector<BitPixel>>(header.width, vector<BitPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			bitmap.at(i).at(j) = FormatConverter::ToBitPixel(graymap.at(i).at(j), header.maxValue);
		}
	return bitmap;
}

shared_ptr<Image> PgmImage::ToPgm()
{
	return std::make_shared<PgmImage>(*this);
}

shared_ptr<Image> PgmImage::ToPpm()
{
	ImageHeader newHeader = GetPpmHeader(header.maxValue);
	auto newColormap = GraymapToColormap();
	return make_shared<PpmImage>(newHeader, newColormap);
}

vector<vector<RgbPixel>> PgmImage::GraymapToColormap()
{
	auto colormap = vector<vector<RgbPixel>>(header.width, vector<RgbPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			colormap.at(i).at(j) = FormatConverter::ToRgbPixel(graymap.at(i).at(j));
		}
	return colormap;
}
