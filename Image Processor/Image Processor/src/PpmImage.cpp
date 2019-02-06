#include "../inc/PpmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/FormatConverter.h"

using std::make_shared;

PpmImage::PpmImage(const ImageMeta& meta, PixelMap<RgbPixel> colormap) : Image(meta),
                                                                             colormap(std::move(colormap))
{
}

shared_ptr<Image> PpmImage::ToPbm()
{
	ImageMeta newMeta = ImageMeta(PBM);
	auto newBitmap = ColormapToBitmap();
	return make_shared<PbmImage>(newMeta, newBitmap);
}

PixelMap<BitPixel> PpmImage::ColormapToBitmap()
{
	auto bitmap = PixelMap<BitPixel>(colormap.GetWidth(), colormap.GetHeight());
	for (size_t i = 0; i < colormap.GetHeight(); ++i)
		for (size_t j = 0; j < colormap.GetWidth(); ++j)
		{
			bitmap(i,j) = FormatConverter::ToBitPixel(colormap(i, j), meta.GetMaxValue());
		}
	return bitmap;
}

shared_ptr<Image> PpmImage::ToPgm()
{
	ImageMeta newMeta = ImageMeta(PGM, meta.GetMaxValue());
	auto newGraymap = ColormapToGraymap();
	return make_shared<PgmImage>(newMeta, newGraymap);
}

PixelMap<GrayPixel> PpmImage::ColormapToGraymap()
{
	auto graymap = PixelMap<GrayPixel>(colormap.GetWidth(), colormap.GetHeight());
	for (size_t i = 0; i < colormap.GetHeight(); ++i)
		for (size_t j = 0; j < colormap.GetWidth(); ++j)
		{
			graymap(i, j) = FormatConverter::ToGrayPixel(colormap(i,j));
		}
	return graymap;
}

shared_ptr<Image> PpmImage::ToPpm()
{
	return std::make_shared<PpmImage>(*this);
}
