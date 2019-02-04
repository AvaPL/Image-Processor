#include "../inc/PgmImage.h"
#include "../inc/FormatConvertingConstants.h"
#include "../inc/PbmImage.h"
#include "../inc/PpmImage.h"

using std::make_shared;

PgmImage::PgmImage(const ImageHeader& header, vector<vector<unsigned short>> graymap): Image(header),
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

vector<vector<char>> PgmImage::GraymapToBitmap()
{
	auto bitmap = vector<vector<char>>(header.width, vector<char>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			bitmap.at(i).at(j) = graymap.at(i).at(j) <= PGM_MAX_GRAY_VALUE / 2 ? '1' : '0';
			//TODO: Remove, add GrayPixel and BitPixel class with conversion.
		}
	return bitmap;
}

shared_ptr<Image> PgmImage::ToPgm()
{
	return std::make_shared<PgmImage>(*this);
}

shared_ptr<Image> PgmImage::ToPpm()
{
	ImageHeader newHeader = GetPpmHeader();
	auto newColormap = GraymapToColormap();
	return make_shared<PpmImage>(newHeader, newColormap);
}

vector<vector<RgbPixel>> PgmImage::GraymapToColormap()
{
	auto colormap = vector<vector<RgbPixel>>(header.width, vector<RgbPixel>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			const unsigned short channelValue = graymap.at(i).at(j);
			colormap.at(i).at(j) = RgbPixel(channelValue, channelValue, channelValue);
			//TODO: Remove, add GrayPixel and BitPixel class with conversion.
		}
	return colormap;
}
