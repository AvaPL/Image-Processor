#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/DefaultValues.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PbmImage::PbmImage(const ImageMeta& meta, PixelMap<BitPixel> bitmap): Image(meta), bitmap(std::move(bitmap))
{
	this->meta.SetMaxValue(PBM_DEFAULT_MAX_VALUE);
}

shared_ptr<Image> PbmImage::ToPbm()
{
	return std::make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::ToPgm()
{
	ImageMeta newMeta = ImageMeta(PGM, PGM_DEFAULT_MAX_GRAY_VALUE);
	auto newGraymap = BitmapToGraymap();
	return make_shared<PgmImage>(newMeta, newGraymap);
}

PixelMap<GrayPixel> PbmImage::BitmapToGraymap()
{
	auto graymap = PixelMap<GrayPixel>(bitmap.GetWidth(), bitmap.GetHeight());
	for (size_t i = 0; i < bitmap.GetHeight(); ++i)
		for (size_t j = 0; j < bitmap.GetWidth(); ++j)
		{
			graymap(i, j) = FormatConverter::ToGrayPixel(bitmap(i, j), PGM_DEFAULT_MAX_GRAY_VALUE);
		}
	return graymap;
}

shared_ptr<Image> PbmImage::ToPpm()
{
	ImageMeta newMeta = ImageMeta(PPM, PPM_DEFAULT_MAX_COLOR_VALUE);
	auto newColormap = BitmapToColormap();
	return make_shared<PpmImage>(newMeta, newColormap);
}

PixelMap<RgbPixel> PbmImage::BitmapToColormap()
{
	auto colormap = PixelMap<RgbPixel>(bitmap.GetWidth(), bitmap.GetHeight());
	for (size_t i = 0; i < bitmap.GetHeight(); ++i)
		for (size_t j = 0; j < bitmap.GetWidth(); ++j)
		{
			colormap(i, j) = FormatConverter::ToRgbPixel(bitmap(i, j), PPM_DEFAULT_MAX_COLOR_VALUE);
		}
	return colormap;
}
