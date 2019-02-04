#include "../inc/PpmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PpmImage::PpmImage(const ImageHeader& header, vector<vector<RgbPixel>> colormap) : Image(header),
                                                                                   colormap(std::move(colormap))
{
	this->header.format = PPM;
}

shared_ptr<Image> PpmImage::ToPbm()
{
	ImageHeader newHeader = GetPbmHeader();
	auto newBitmap = ColormapToBitmap();
	return make_shared<PbmImage>(newHeader, newBitmap);
}

vector<vector<BitPixel>> PpmImage::ColormapToBitmap()
{
	auto bitmap = vector<vector<BitPixel>>(header.width, vector<BitPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			bitmap.at(i).at(j) = FormatConverter::ToBitPixel(colormap.at(i).at(j), header.maxValue);
		}
	return bitmap;
}

shared_ptr<Image> PpmImage::ToPgm()
{
	ImageHeader newHeader = GetPgmHeader(header.maxValue);
	auto newGraymap = ColormapToGraymap();
	return make_shared<PgmImage>(newHeader, newGraymap);
}

vector<vector<GrayPixel>> PpmImage::ColormapToGraymap()
{
	auto graymap = vector<vector<GrayPixel>>(header.width, vector<GrayPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			graymap.at(i).at(j) = FormatConverter::ToGrayPixel(colormap.at(i).at(j));
		}
	return graymap;
}

shared_ptr<Image> PpmImage::ToPpm()
{
	return std::make_shared<PpmImage>(*this);
}
