#include "../inc/PgmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PgmImage::PgmImage(const ImageHeader& header, PixelMap<GrayPixel> graymap): Image(header),
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

PixelMap<BitPixel> PgmImage::GraymapToBitmap()
{
	auto bitmap = PixelMap<BitPixel>(header.width, header.height);
	for (auto i = 0; i < header.height; ++i)
		for (auto j = 0; j < header.width; ++j)
		{
			bitmap(i, j) = FormatConverter::ToBitPixel(graymap(i, j), header.maxValue);
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

PixelMap<RgbPixel> PgmImage::GraymapToColormap()
{
	auto colormap = PixelMap<RgbPixel>(header.width, header.height);
	for (auto i = 0; i < header.height; ++i)
		for (auto j = 0; j < header.width; ++j)
		{
			colormap(i, j) = FormatConverter::ToRgbPixel(graymap(i, j));
		}
	return colormap;
}
