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
	ImageMeta newMeta = ImageMeta(PBM, meta.GetComments());
	auto newBitmap = FormatConverter::ToBitmap(colormap, GetMaxValue());
	return make_shared<PbmImage>(newMeta, newBitmap);
}

shared_ptr<Image> PpmImage::ToPgm()
{
	ImageMeta newMeta = ImageMeta(PGM, meta.GetComments(), meta.GetMaxValue());
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
	for (auto& rgbPixel : resultColormap)
	{
		for (auto& channel : rgbPixel)
			channel = static_cast<unsigned short>(filterer.Negative(channel));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::Tresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& rgbPixel : resultColormap)
	{
		for (auto& channel : rgbPixel)
			channel = static_cast<unsigned short>(filterer.Tresholding(channel, treshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::BlackTresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	for (auto& rgbPixel : resultColormap)
	{
		for (auto& channel : rgbPixel)
			channel = static_cast<unsigned short>(Filterer::BlackTresholding(channel, treshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::WhiteTresholding(const unsigned short treshold)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& rgbPixel : resultColormap)
	{
		for (auto& channel : rgbPixel)
			channel = static_cast<unsigned short>(filterer.WhiteTresholding(channel, treshold));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::GammaCorrection(const double gamma)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& rgbPixel : resultColormap)
	{
		for (auto& channel : rgbPixel)
			channel = static_cast<unsigned short>(filterer.GammaCorrection(channel, gamma));
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold)
{
	auto resultColormap = colormap;
	Filterer filterer(GetMaxValue());
	for (auto& rgbPixel : resultColormap)
	{
		for (auto& channel : rgbPixel)
			channel = static_cast<unsigned short>(filterer.LevelChange(channel, blackTreshold, whiteTreshold));
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
				resultColormap(i, j) = ContourEveryChannel(colormap(i, j), colormap(i + 1, j), colormap(i, j + 1));
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
				resultColormap(i, j) = BlurEveryChannelHorizontaly(colormap(i, j - 1), colormap(i, j),
				                                                   colormap(i, j + 1));
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
				resultColormap(i, j) =
					BlurEveryChannelVerticaly(colormap(i - 1, j), colormap(i, j), colormap(i + 1, j));
			}
		}
	return make_shared<PpmImage>(meta, resultColormap);
}

shared_ptr<Image> PpmImage::HistogramStretching()
{
	auto resultColormap = colormap;
	const auto minExistingValues = FindMinExistingValues();
	const auto maxExistingValues = FindMaxExistingValues();
	const Filterer filterer(GetMaxValue());
	for (auto& element : resultColormap)
	{
		element = StretchEveryChannelsHistogram(filterer, element, minExistingValues, maxExistingValues);
	}
	return make_shared<PpmImage>(meta, resultColormap);
}

RgbPixel PpmImage::ContourEveryChannel(const RgbPixel& pixel, const RgbPixel& pixelBelow,
                                       const RgbPixel& pixelToTheRight)
{
	RgbPixel result;
	result.red = static_cast<unsigned short>(Filterer::Contouring(pixel.red, pixelBelow.red, pixelToTheRight.red));
	result.green = static_cast<unsigned short>(Filterer::Contouring(pixel.green, pixelBelow.green,
	                                                                pixelToTheRight.green));
	result.blue = static_cast<unsigned short>(Filterer::Contouring(pixel.blue, pixelBelow.blue, pixelToTheRight.blue));
	return result;
}

RgbPixel PpmImage::BlurEveryChannelHorizontaly(const RgbPixel& pixelToTheLeft, const RgbPixel& pixel,
                                               const RgbPixel& pixelToTheRight)
{
	RgbPixel result;
	result.red = static_cast<unsigned short>(Filterer::HorizontalBlur(pixelToTheLeft.red, pixel.red,
	                                                                  pixelToTheRight.red));
	result.green = static_cast<unsigned short>(Filterer::HorizontalBlur(pixelToTheLeft.green, pixel.green,
	                                                                    pixelToTheRight.green));
	result.blue = static_cast<unsigned short>(Filterer::HorizontalBlur(pixelToTheLeft.blue, pixel.blue,
	                                                                   pixelToTheRight.blue));
	return result;
}

RgbPixel PpmImage::BlurEveryChannelVerticaly(const RgbPixel& pixelAbove, const RgbPixel& pixel,
                                             const RgbPixel& pixelBelow)
{
	RgbPixel result;
	result.red = static_cast<unsigned short>(Filterer::VerticalBlur(pixelAbove.red, pixel.red,
	                                                                pixelBelow.red));
	result.green = static_cast<unsigned short>(Filterer::VerticalBlur(pixelAbove.green, pixel.green,
	                                                                  pixelBelow.green));
	result.blue = static_cast<unsigned short>(Filterer::VerticalBlur(pixelAbove.blue, pixel.blue,
	                                                                 pixelBelow.blue));
	return result;
}

RgbPixel PpmImage::StretchEveryChannelsHistogram(const Filterer& filterer, const RgbPixel& pixel,
                                                 const RgbPixel& minExistingValues,
                                                 const RgbPixel& maxExistingValues)
{
	RgbPixel result;
	result.red = static_cast<unsigned short>(filterer.HistogramStretching(pixel.red, minExistingValues.red,
	                                                                      maxExistingValues.red));
	result.green = static_cast<unsigned short>(filterer.HistogramStretching(pixel.green, minExistingValues.green,
	                                                                        maxExistingValues.green));
	result.blue = static_cast<unsigned short>(filterer.HistogramStretching(pixel.blue, minExistingValues.blue,
	                                                                       maxExistingValues.blue));
	return result;
}

RgbPixel PpmImage::FindMinExistingValues()
{
	RgbPixel minimumChannelValues(GetMaxValue(), GetMaxValue(), GetMaxValue());
	for (const auto& element : colormap)
	{
		if (element.red < minimumChannelValues.red) minimumChannelValues.red = element.red;
		if (element.green < minimumChannelValues.green) minimumChannelValues.green = element.green;
		if (element.blue < minimumChannelValues.blue) minimumChannelValues.blue = element.blue;
	}
	return minimumChannelValues;
}

RgbPixel PpmImage::FindMaxExistingValues()
{
	RgbPixel maximumChannelValues(0, 0, 0);
	for (const auto& element : colormap)
	{
		if (element.red > maximumChannelValues.red) maximumChannelValues.red = element.red;
		if (element.green > maximumChannelValues.green) maximumChannelValues.green = element.green;
		if (element.blue > maximumChannelValues.blue) maximumChannelValues.blue = element.blue;
	}
	return maximumChannelValues;
}
