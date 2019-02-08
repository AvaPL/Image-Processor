#include "../inc/PpmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/FormatConverter.h"
#include "../inc/Filterer.h"

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
	Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(filterer.Negative(element.red));
		element.green = static_cast<unsigned short>(filterer.Negative(element.green));
		element.blue = static_cast<unsigned short>(filterer.Negative(element.blue));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::Tresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(filterer.Tresholding(element.red, treshold));
		element.green = static_cast<unsigned short>(filterer.Tresholding(element.green, treshold));
		element.blue = static_cast<unsigned short>(filterer.Tresholding(element.blue, treshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::BlackTresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(Filterer::BlackTresholding(element.red, treshold));
		element.green = static_cast<unsigned short>(Filterer::BlackTresholding(element.green, treshold));
		element.blue = static_cast<unsigned short>(Filterer::BlackTresholding(element.blue, treshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::WhiteTresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(filterer.WhiteTresholding(element.red, treshold));
		element.green = static_cast<unsigned short>(filterer.WhiteTresholding(element.green, treshold));
		element.blue = static_cast<unsigned short>(filterer.WhiteTresholding(element.blue, treshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::GammaCorrection(const double gamma)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(filterer.GammaCorrection(element.red, gamma));
		element.green = static_cast<unsigned short>(filterer.GammaCorrection(element.green, gamma));
		element.blue = static_cast<unsigned short>(filterer.GammaCorrection(element.blue, gamma));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(filterer.LevelChange(element.red, blackTreshold, whiteTreshold));
		element.green = static_cast<unsigned short>(filterer.LevelChange(element.green, blackTreshold, whiteTreshold));
		element.blue = static_cast<unsigned short>(filterer.LevelChange(element.blue, blackTreshold, whiteTreshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
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
