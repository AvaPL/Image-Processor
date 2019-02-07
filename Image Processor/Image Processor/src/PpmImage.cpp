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

//TODO: Implement missing operations.

shared_ptr<Image> PpmImage::Negative()
{
	auto resultColormap = colormap;
	for (auto& element : resultColormap)
	{
		element.red = GetMaxValue() - element.red;
		element.green = GetMaxValue() - element.green;
		element.blue = GetMaxValue() - element.blue;
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::Tresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	for (auto& element : resultColormap)
	{
		element.red = element.red <= treshold ? 0 : GetMaxValue();
		element.green = element.green <= treshold ? 0 : GetMaxValue();
		element.blue = element.blue <= treshold ? 0 : GetMaxValue();
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::BlackTresholding(const unsigned short treshold)
{
	return nullptr;
}

shared_ptr<Image> PpmImage::WhiteTresholding(const unsigned short treshold)
{
	return nullptr;
}

shared_ptr<Image> PpmImage::GammaCorrection(double gamma)
{
	return nullptr;
}

shared_ptr<Image> PpmImage::LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold)
{
	return nullptr;
}

shared_ptr<Image> PpmImage::Contouring()
{
	return nullptr;
}

shared_ptr<Image> PpmImage::HorizontalBlur()
{
	return nullptr;
}

shared_ptr<Image> PpmImage::VerticalBlur()
{
	return nullptr;
}

shared_ptr<Image> PpmImage::HistogramStretching()
{
	return nullptr;
}
