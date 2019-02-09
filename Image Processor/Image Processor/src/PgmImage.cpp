#include "../inc/PgmImage.h"
#include "../inc/PbmImage.h"
#include "../inc/PpmImage.h"
#include "../inc/FormatConverter.h"
#include "../inc/Filterer.h"

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

shared_ptr<Image> PgmImage::Negative()
{
	auto resultGraymap = graymap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(filterer.Negative(element.value));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::Tresholding(const unsigned short treshold)
{
	auto resultGraymap = graymap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(filterer.Tresholding(element.value, treshold));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::BlackTresholding(const unsigned short treshold)
{
	auto resultGraymap = graymap;
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(Filterer::BlackTresholding(element.value, treshold));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::WhiteTresholding(const unsigned short treshold)
{
	auto resultGraymap = graymap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(filterer.WhiteTresholding(element.value, treshold));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::GammaCorrection(const double gamma)
{
	auto resultGraymap = graymap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(filterer.GammaCorrection(element.value, gamma));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold)
{
	auto resultGraymap = graymap;
	Filterer filterer(GetMaxValue());
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(filterer.LevelChange(element.value, blackTreshold, whiteTreshold));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::Contouring()
{
	auto resultGraymap = graymap;
	for (size_t j = 0; j < graymap.GetWidth(); ++j)
		for (size_t i = 0; i < graymap.GetHeight(); ++i)
		{
			if (graymap.IsIndexCorrect(i + 1, j) && graymap.IsIndexCorrect(i, j + 1))
				resultGraymap(i, j).value = static_cast<unsigned short>(Filterer::Contouring(
					graymap(i, j).value, graymap(i + 1, j).value, graymap(i, j + 1).value));
		}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::HorizontalBlur()
{
	auto resultGraymap = graymap;
	for (size_t j = 0; j < graymap.GetWidth(); ++j)
		for (size_t i = 0; i < graymap.GetHeight(); ++i)
		{
			if (graymap.IsIndexCorrect(i, j - 1) && graymap.IsIndexCorrect(i, j + 1))
				resultGraymap(i, j).value = static_cast<unsigned short>(Filterer::HorizontalBlur(
					graymap(i, j - 1).value, graymap(i, j).value, graymap(i, j + 1).value));
		}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::VerticalBlur()
{
	auto resultGraymap = graymap;
	for (size_t j = 0; j < graymap.GetWidth(); ++j)
		for (size_t i = 0; i < graymap.GetHeight(); ++i)
		{
			if (graymap.IsIndexCorrect(i - 1, j) && graymap.IsIndexCorrect(i + 1, j))
				resultGraymap(i, j).value = static_cast<unsigned short>(Filterer::VerticalBlur(
					graymap(i - 1, j).value, graymap(i, j).value, graymap(i + 1, j).value));
		}
	return make_shared<PgmImage>(meta, resultGraymap);
}

shared_ptr<Image> PgmImage::HistogramStretching()
{
	auto resultGraymap = graymap;
	const auto existingMinPixel = FindMinExistingValue();
	const auto existingMaxPixel = FindMaxExistingValue();
	Filterer filterer(GetMaxValue());
	for (auto& element : resultGraymap)
	{
		element.value = static_cast<unsigned short>(filterer.HistogramStretching(
			element.value, existingMinPixel, existingMaxPixel));
	}
	return make_shared<PgmImage>(meta, resultGraymap);
}

unsigned short PgmImage::FindMinExistingValue()
{
	unsigned short minimum = GetMaxValue();
	for (const auto& element : graymap)
	{
		if (element.value < minimum) minimum = element.value;
	}
	return minimum;
}

unsigned short PgmImage::FindMaxExistingValue()
{
	unsigned short maximum = 0;
	for (const auto& element : graymap)
	{
		if (element.value > maximum) maximum = element.value;
	}
	return maximum;
}
