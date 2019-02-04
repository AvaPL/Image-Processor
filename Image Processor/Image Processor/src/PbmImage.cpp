#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/DefaultValues.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PbmImage::PbmImage(const ImageHeader& header, vector<vector<BitPixel>> bitmap): Image(header), bitmap(std::move(bitmap))
{
	this->header.format = PBM;
	this->header.maxValue = PBM_DEFAULT_MAX_VALUE;
}

shared_ptr<Image> PbmImage::ToPbm()
{
	return std::make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::ToPgm()
{
	ImageHeader newHeader = GetPgmHeader(PGM_DEFAULT_MAX_GRAY_VALUE);
	auto newGraymap = BitmapToGraymap();
	return make_shared<PgmImage>(newHeader, newGraymap);
}

vector<vector<GrayPixel>> PbmImage::BitmapToGraymap()
{
	auto graymap = vector<vector<GrayPixel>>(header.width, vector<GrayPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			graymap.at(i).at(j) = FormatConverter::ToGrayPixel(bitmap.at(i).at(j), PGM_DEFAULT_MAX_GRAY_VALUE);
		}
	return graymap;
}

shared_ptr<Image> PbmImage::ToPpm()
{
	ImageHeader newHeader = GetPpmHeader(PPM_DEFAULT_MAX_COLOR_VALUE);
	auto newColormap = BitmapToColormap();
	return make_shared<PpmImage>(newHeader, newColormap);
}

vector<vector<RgbPixel>> PbmImage::BitmapToColormap()
{
	auto colormap = vector<vector<RgbPixel>>(header.width, vector<RgbPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			colormap.at(i).at(j) = FormatConverter::ToRgbPixel(bitmap.at(i).at(j), PPM_DEFAULT_MAX_COLOR_VALUE);
		}
	return colormap;
}
