#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/DefaultValues.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PbmImage::PbmImage(const ImageHeader& header, PixelMap<BitPixel> bitmap): Image(header), bitmap(std::move(bitmap))
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

PixelMap<GrayPixel> PbmImage::BitmapToGraymap()
{
	auto graymap = PixelMap<GrayPixel>(bitmap.Width(), bitmap.Height());
	for (auto i = 0; i < bitmap.Height(); ++i)
		for (auto j = 0; j < bitmap.Width(); ++j)
		{
			graymap(i, j) = FormatConverter::ToGrayPixel(bitmap(i, j), PGM_DEFAULT_MAX_GRAY_VALUE);
		}
	return graymap;
}

shared_ptr<Image> PbmImage::ToPpm()
{
	ImageHeader newHeader = GetPpmHeader(PPM_DEFAULT_MAX_COLOR_VALUE);
	auto newColormap = BitmapToColormap();
	return make_shared<PpmImage>(newHeader, newColormap);
}

PixelMap<RgbPixel> PbmImage::BitmapToColormap()
{
	auto colormap = PixelMap<RgbPixel>(bitmap.Width(), bitmap.Height());
	for (auto i = 0; i < bitmap.Height(); ++i)
		for (auto j = 0; j < bitmap.Width(); ++j)
		{
			colormap(i, j) = FormatConverter::ToRgbPixel(bitmap(i, j), PPM_DEFAULT_MAX_COLOR_VALUE);
		}
	return colormap;
}
