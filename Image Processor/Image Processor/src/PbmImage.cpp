#include "../inc/PbmImage.h"
#include "../inc/FormatConvertingConstants.h"
#include "../inc/PgmImage.h"
#include "../inc/PpmImage.h"

using std::make_shared;

PbmImage::PbmImage(const ImageHeader& header, vector<vector<char>> bitmap): Image(header), bitmap(std::move(bitmap))
{
	this->header.format = PBM;
	this->header.maxValue = PBM_MAX_VALUE;
}

shared_ptr<Image> PbmImage::ToPbm()
{
	return std::make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::ToPgm()
{
	ImageHeader newHeader = GetPgmHeader();
	auto newGraymap = BitmapToGraymap();
	return make_shared<PgmImage>(newHeader, newGraymap);
}

vector<vector<unsigned short>> PbmImage::BitmapToGraymap()
{
	auto graymap = vector<vector<unsigned short>>(header.width, vector<unsigned short>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			graymap.at(i).at(j) = bitmap.at(i).at(j) == '0' ? PGM_MAX_GRAY_VALUE : 0;
			//TODO: Remove, add GrayPixel and BitPixel class with conversion.
		}
	return graymap;
}

shared_ptr<Image> PbmImage::ToPpm()
{
	ImageHeader newHeader = GetPpmHeader();
	auto newColormap = BitmapToColormap();
	return make_shared<PpmImage>(newHeader, newColormap);
}

vector<vector<RgbPixel>> PbmImage::BitmapToColormap()
{
	auto colormap = vector<vector<RgbPixel>>(header.width, vector<RgbPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			colormap.at(i).at(j) = bitmap.at(i).at(j) == '0'
				                       ? RgbPixel(PPM_MAX_COLOR_VALUE, PPM_MAX_COLOR_VALUE, PPM_MAX_COLOR_VALUE)
				                       : RgbPixel(0, 0, 0);
			//TODO: Remove, add GrayPixel and BitPixel class with conversion.
		}
	return colormap;
}
