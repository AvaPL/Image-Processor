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

//TODO: Implement missing operations.

shared_ptr<Image> PgmImage::Negative()
{
	auto resultGraymap = graymap;
	for (auto& element : resultGraymap)
	{
		element.value = GetMaxValue() - element.value;
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::Tresholding(const unsigned short treshold)
{
	auto resultGraymap = graymap;
	for (auto& element : resultGraymap)
	{
		element.value = element.value <= treshold ? 0 : GetMaxValue();
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::BlackTresholding(const unsigned short treshold)
{
	return nullptr;
}

shared_ptr<Image> PgmImage::WhiteTresholding(const unsigned short treshold)
{
	return nullptr;
}

shared_ptr<Image> PgmImage::GammaCorrection(double gamma)
{
	return nullptr;
}

shared_ptr<Image> PgmImage::LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold)
{
	return nullptr;
}

shared_ptr<Image> PgmImage::Contouring()
{
	return nullptr;
}

shared_ptr<Image> PgmImage::HorizontalBlur()
{
	return nullptr;
}

shared_ptr<Image> PgmImage::VerticalBlur()
{
	return nullptr;
}

shared_ptr<Image> PgmImage::HistogramStretching()
{
	return nullptr;
}
