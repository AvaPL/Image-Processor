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
	auto newBitmap = FormatConverter::ToBitmap(graymap, GetMaxValue());
	return make_shared<PbmImage>(newMeta, newBitmap);
}
shared_ptr<Image> PgmImage::ToPgm()
{
	return std::make_shared<PgmImage>(*this);
}

shared_ptr<Image> PgmImage::ToPpm()
{
	ImageMeta newMeta = ImageMeta(PPM, meta.GetMaxValue());
	auto newColormap = FormatConverter::ToColormap(graymap);
	return make_shared<PpmImage>(newMeta, newColormap);
}