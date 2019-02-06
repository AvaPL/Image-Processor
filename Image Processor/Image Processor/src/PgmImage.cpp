#include "../inc/PgmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PgmImage::PgmImage(const ImageMeta& meta, PixelMap<GrayPixel> graymap): Image(meta),
                                                                            graymap(std::move(graymap))
{
}

shared_ptr<Image> PgmImage::ToPbm()
{
	ImageMeta newMeta = ImageMeta(PBM);
	auto newBitmap = GraymapToBitmap();
	return make_shared<PbmImage>(newMeta, newBitmap);
}

PixelMap<BitPixel> PgmImage::GraymapToBitmap()
{
	auto bitmap = PixelMap<BitPixel>(graymap.GetWidth(), graymap.GetHeight());
	for (size_t i = 0; i < graymap.GetHeight(); ++i)
		for (size_t j = 0; j < graymap.GetWidth(); ++j)
		{
			bitmap(i, j) = FormatConverter::ToBitPixel(graymap(i, j), meta.GetMaxValue());
		}
	return bitmap;
}

shared_ptr<Image> PgmImage::ToPgm()
{
	return std::make_shared<PgmImage>(*this);
}

shared_ptr<Image> PgmImage::ToPpm()
{
	ImageMeta newMeta = ImageMeta(PPM, meta.GetMaxValue());
	auto newColormap = GraymapToColormap();
	return make_shared<PpmImage>(newMeta, newColormap);
}

PixelMap<RgbPixel> PgmImage::GraymapToColormap()
{
	auto colormap = PixelMap<RgbPixel>(graymap.GetWidth(), graymap.GetHeight());
	for (size_t i = 0; i < graymap.GetHeight(); ++i)
		for (size_t j = 0; j < graymap.GetWidth(); ++j)
		{
			colormap(i, j) = FormatConverter::ToRgbPixel(graymap(i, j));
		}
	return colormap;
}
