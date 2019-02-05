#include "../inc/PpmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PpmImage::PpmImage(const ImageHeader& header, PixelMap<RgbPixel> colormap) : Image(header),
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

PixelMap<BitPixel> PpmImage::ColormapToBitmap()
{
	auto bitmap = PixelMap<BitPixel>(header.width, header.height);
	for (auto i = 0; i < header.height; ++i)
		for (auto j = 0; j < header.width; ++j)
		{
			bitmap(i,j) = FormatConverter::ToBitPixel(colormap(i, j), header.maxValue);
		}
	return bitmap;
}

shared_ptr<Image> PpmImage::ToPgm()
{
	ImageHeader newHeader = GetPgmHeader(header.maxValue);
	auto newGraymap = ColormapToGraymap();
	return make_shared<PgmImage>(newHeader, newGraymap);
}

PixelMap<GrayPixel> PpmImage::ColormapToGraymap()
{
	auto graymap = PixelMap<GrayPixel>(header.width, header.height);
	for (auto i = 0; i < header.height; ++i)
		for (auto j = 0; j < header.width; ++j)
		{
			graymap(i, j) = FormatConverter::ToGrayPixel(colormap(i,j));
		}
	return graymap;
}

shared_ptr<Image> PpmImage::ToPpm()
{
	return std::make_shared<PpmImage>(*this);
}
