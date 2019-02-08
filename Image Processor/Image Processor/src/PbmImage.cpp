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
	auto newGraymap = FormatConverter::ToGraymap(bitmap);
	return make_shared<PgmImage>(newMeta, newGraymap);
}

shared_ptr<Image> PbmImage::ToPpm()
{
	ImageMeta newMeta = ImageMeta(PPM, PPM_DEFAULT_MAX_COLOR_VALUE);
	auto newColormap = FormatConverter::ToColormap(bitmap);
	return make_shared<PpmImage>(newMeta, newColormap);
}

//TODO: Implement missing operations.

shared_ptr<Image> PbmImage::Negative()
{
	auto resultBitmap = bitmap;
	for (auto& element : resultBitmap)
	{
		element.isBlack = !element.isBlack;
	}
	return make_shared<PbmImage>(meta, resultBitmap);
}

shared_ptr<Image> PbmImage::Tresholding(const unsigned short treshold)
{
	//Unsupported.
	return make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::BlackTresholding(const unsigned short treshold)
{
	//Unsupported.
	return make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::WhiteTresholding(const unsigned short treshold)
{
	//Unsupported.
	return make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::GammaCorrection(const double gamma)
{
	//Unsupported.
	return make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold)
{
	//Unsupported.
	return make_shared<PbmImage>(*this);
}

shared_ptr<Image> PbmImage::Contouring()
{
	return nullptr;
}

shared_ptr<Image> PbmImage::HorizontalBlur()
{
	return nullptr;
}

shared_ptr<Image> PbmImage::VerticalBlur()
{
	return nullptr;
}

shared_ptr<Image> PbmImage::HistogramStretching()
{
	return nullptr;
}
