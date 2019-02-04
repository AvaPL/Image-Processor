#include "../inc/PpmImage.h"
#include "../inc/FormatConvertingConstants.h"
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"

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

vector<vector<char>> PpmImage::ColormapToBitmap()
{
	auto bitmap = vector<vector<char>>(header.width, vector<char>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			bitmap.at(i).at(j) = RgbPixelToBitValue(colormap.at(i).at(j));
			//TODO: Remove, add GrayPixel and BitPixel class with conversion.
		}
	return bitmap;
}

char PpmImage::RgbPixelToBitValue(const RgbPixel& pixel)
{
	return RgbPixelToGrayValue(pixel) <= PGM_MAX_GRAY_VALUE/2 ? '1' : '0';
}

shared_ptr<Image> PpmImage::ToPgm()
{
	ImageHeader newHeader = GetPgmHeader();
	auto newGraymap = ColormapToGraymap();
	return make_shared<PgmImage>(newHeader, newGraymap);
}

vector<vector<unsigned short>> PpmImage::ColormapToGraymap()
{
	auto graymap = vector<vector<unsigned short>>(header.width, vector<unsigned short>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			graymap.at(i).at(j) = RgbPixelToGrayValue(colormap.at(i).at(j));
		}
	return graymap;
}

unsigned short PpmImage::RgbPixelToGrayValue(const RgbPixel& pixel)
{
	return (pixel.red + pixel.green + pixel.blue) / 3;
}

shared_ptr<Image> PpmImage::ToPpm()
{
	return std::make_shared<PpmImage>(*this);
}
