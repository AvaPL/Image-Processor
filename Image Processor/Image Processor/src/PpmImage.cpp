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
	auto resultColormap = colormap;
	for (size_t j = 0; j < colormap.GetWidth(); ++j)
		for (size_t i = 0; i < colormap.GetHeight(); ++i)
		{
			if (colormap.IsIndexCorrect(i + 1, j) && colormap.IsIndexCorrect(i, j + 1))
			{
				resultColormap(i, j).red = static_cast<unsigned short>(Filterer::Contouring(
					colormap(i, j).red, colormap(i + 1, j).red, colormap(i, j + 1).red));
				resultColormap(i, j).green = static_cast<unsigned short>(Filterer::Contouring(
					colormap(i, j).green, colormap(i + 1, j).green, colormap(i, j + 1).green));
				resultColormap(i, j).blue = static_cast<unsigned short>(Filterer::Contouring(
					colormap(i, j).blue, colormap(i + 1, j).blue, colormap(i, j + 1).blue));
			}
		}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::HorizontalBlur()
{
	auto resultColormap = colormap;
	for (size_t j = 0; j < colormap.GetWidth(); ++j)
		for (size_t i = 0; i < colormap.GetHeight(); ++i)
		{
			if (colormap.IsIndexCorrect(i, j - 1) && colormap.IsIndexCorrect(i, j + 1))
			{
				resultColormap(i, j).red = static_cast<unsigned short>(Filterer::HorizontalBlur(
					colormap(i, j - 1).red, colormap(i, j).red, colormap(i, j + 1).red));
				resultColormap(i, j).green = static_cast<unsigned short>(Filterer::HorizontalBlur(
					colormap(i, j - 1).green, colormap(i, j).green, colormap(i, j + 1).green));
				resultColormap(i, j).blue = static_cast<unsigned short>(Filterer::HorizontalBlur(
					colormap(i, j - 1).blue, colormap(i, j).blue, colormap(i, j + 1).blue));
			}
		}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::VerticalBlur()
{
	auto resultColormap = colormap;
	for (size_t j = 0; j < colormap.GetWidth(); ++j)
		for (size_t i = 0; i < colormap.GetHeight(); ++i)
		{
			if (colormap.IsIndexCorrect(i - 1, j) && colormap.IsIndexCorrect(i + 1, j))
			{
				resultColormap(i, j).red = static_cast<unsigned short>(Filterer::HorizontalBlur(
					colormap(i - 1, j).red, colormap(i, j).red, colormap(i + 1, j).red));
				resultColormap(i, j).green = static_cast<unsigned short>(Filterer::HorizontalBlur(
					colormap(i - 1, j).green, colormap(i, j).green, colormap(i + 1, j).green));
				resultColormap(i, j).blue = static_cast<unsigned short>(Filterer::HorizontalBlur(
					colormap(i - 1, j).blue, colormap(i, j).blue, colormap(i + 1, j).blue));
			}
		}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::HistogramStretching()
{
	auto resultColormap = colormap;
	const auto existingMinRedPixel = FindMinExistingRedValue();
	const auto existingMaxRedPixel = FindMaxExistingRedValue();
	const auto existingMinGreenPixel = FindMinExistingGreenValue();
	const auto existingMaxGreenPixel = FindMaxExistingGreenValue();
	const auto existingMinBluePixel = FindMinExistingBlueValue();
	const auto existingMaxBluePixel = FindMaxExistingBlueValue();
	Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element.red = static_cast<unsigned short>(filterer.HistogramStretching(
			element.red, existingMinRedPixel, existingMaxRedPixel));
		element.green = static_cast<unsigned short>(filterer.HistogramStretching(
			element.green, existingMinGreenPixel, existingMaxGreenPixel));
		element.blue = static_cast<unsigned short>(filterer.HistogramStretching(
			element.blue, existingMinBluePixel, existingMaxBluePixel));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

unsigned short PpmImage::FindMinExistingRedValue()
{
	unsigned short minimum = GetMaxValue();
	for (const auto& element : colormap)
	{
		if (element.red < minimum) minimum = element.red;
	}
	return minimum;
}

unsigned short PpmImage::FindMaxExistingRedValue()
{
	unsigned short maximum = 0;
	for (const auto& element : colormap)
	{
		if (element.red > maximum) maximum = element.red;
	}
	return maximum;
}

unsigned short PpmImage::FindMinExistingGreenValue()
{
	unsigned short minimum = GetMaxValue();
	for (const auto& element : colormap)
	{
		if (element.green < minimum) minimum = element.green;
	}
	return minimum;
}

unsigned short PpmImage::FindMaxExistingGreenValue()
{
	unsigned short maximum = 0;
	for (const auto& element : colormap)
	{
		if (element.green > maximum) maximum = element.green;
	}
	return maximum;
}

unsigned short PpmImage::FindMinExistingBlueValue()
{
	unsigned short minimum = GetMaxValue();
	for (const auto& element : colormap)
	{
		if (element.blue < minimum) minimum = element.blue;
	}
	return minimum;
}

unsigned short PpmImage::FindMaxExistingBlueValue()
{
	unsigned short maximum = 0;
	for (const auto& element : colormap)
	{
		if (element.blue > maximum) maximum = element.blue;
	}
	return maximum;
}
