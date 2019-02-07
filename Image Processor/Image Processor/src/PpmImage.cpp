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
	auto newBitmap = FormatConverter::ToBitmap(colormap, GetMaxValue());
	return make_shared<PbmImage>(newMeta, newBitmap);
}

shared_ptr<Image> PpmImage::ToPgm()
{
	ImageMeta newMeta = ImageMeta(PGM, meta.GetMaxValue());
	auto newGraymap = FormatConverter::ToGraymap(colormap);
	return make_shared<PgmImage>(newMeta, newGraymap);
}

shared_ptr<Image> PpmImage::ToPpm()
{
	return std::make_shared<PpmImage>(*this);
}
