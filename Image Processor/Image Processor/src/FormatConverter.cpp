#include "../inc/FormatConverter.h"
#include "../inc/DefaultValues.h"

BitPixel FormatConverter::ToBitPixel(const GrayPixel& grayPixel, const unsigned short maxGrayValue)
{
	const bool isBlack = grayPixel.value <= maxGrayValue / 2;
	return BitPixel(isBlack);
}

BitPixel FormatConverter::ToBitPixel(const RgbPixel& rgbPixel, const unsigned short maxColorValue)
{
	const auto grayValue = ToGrayPixel(rgbPixel).value;
	const bool isBlack = grayValue <= maxColorValue / 2;
	return BitPixel(isBlack);
}

GrayPixel FormatConverter::ToGrayPixel(const BitPixel& bitPixel, const unsigned short maxGrayValue)
{
	const unsigned short grayValue = bitPixel.isBlack ? 0 : maxGrayValue;
	return GrayPixel(grayValue);
}

GrayPixel FormatConverter::ToGrayPixel(const RgbPixel& rgbPixel)
{
	return GrayPixel((rgbPixel.red + rgbPixel.green + rgbPixel.blue) / 3);
}

RgbPixel FormatConverter::ToRgbPixel(const BitPixel& bitPixel, const unsigned short maxColorValue)
{
	const unsigned short colorChannelValue = ToGrayPixel(bitPixel, maxColorValue).value;
	return RgbPixel(colorChannelValue, colorChannelValue, colorChannelValue);
}

RgbPixel FormatConverter::ToRgbPixel(const GrayPixel& grayPixel)
{
	return RgbPixel(grayPixel.value, grayPixel.value, grayPixel.value);
}

PixelMap<BitPixel> FormatConverter::ToBitmap(const PixelMap<GrayPixel>& graymap, const unsigned short maxGrayValue)
{
	auto bitmap = PixelMap<BitPixel>(graymap.GetWidth(), graymap.GetHeight());
	for (size_t i = 0; i < graymap.GetHeight(); ++i)
		for (size_t j = 0; j < graymap.GetWidth(); ++j)
		{
			bitmap(i, j) = ToBitPixel(graymap(i, j), maxGrayValue);
		}
	return bitmap;
}

PixelMap<BitPixel> FormatConverter::ToBitmap(const PixelMap<RgbPixel>& colormap, const unsigned short maxColorValue)
{
	auto bitmap = PixelMap<BitPixel>(colormap.GetWidth(), colormap.GetHeight());
	for (size_t i = 0; i < colormap.GetHeight(); ++i)
		for (size_t j = 0; j < colormap.GetWidth(); ++j)
		{
			bitmap(i, j) = ToBitPixel(colormap(i, j), maxColorValue);
		}
	return bitmap;
}

PixelMap<GrayPixel> FormatConverter::ToGraymap(const PixelMap<BitPixel>& bitmap)
{
	auto graymap = PixelMap<GrayPixel>(bitmap.GetWidth(), bitmap.GetHeight());
	for (size_t i = 0; i < bitmap.GetHeight(); ++i)
		for (size_t j = 0; j < bitmap.GetWidth(); ++j)
		{
			graymap(i, j) = ToGrayPixel(bitmap(i, j), PGM_DEFAULT_MAX_GRAY_VALUE);
		}
	return graymap;
}

PixelMap<GrayPixel> FormatConverter::ToGraymap(const PixelMap<RgbPixel>& colormap)
{
	auto graymap = PixelMap<GrayPixel>(colormap.GetWidth(), colormap.GetHeight());
	for (size_t i = 0; i < colormap.GetHeight(); ++i)
		for (size_t j = 0; j < colormap.GetWidth(); ++j)
		{
			graymap(i, j) = ToGrayPixel(colormap(i, j));
		}
	return graymap;
}

PixelMap<RgbPixel> FormatConverter::ToColormap(const PixelMap<BitPixel>& bitmap)
{
	auto colormap = PixelMap<RgbPixel>(bitmap.GetWidth(), bitmap.GetHeight());
	for (size_t i = 0; i < bitmap.GetHeight(); ++i)
		for (size_t j = 0; j < bitmap.GetWidth(); ++j)
		{
			colormap(i, j) = ToRgbPixel(bitmap(i, j), PPM_DEFAULT_MAX_COLOR_VALUE);
		}
	return colormap;
}

PixelMap<RgbPixel> FormatConverter::ToColormap(const PixelMap<GrayPixel>& graymap)
{
	auto colormap = PixelMap<RgbPixel>(graymap.GetWidth(), graymap.GetHeight());
	for (size_t i = 0; i < graymap.GetHeight(); ++i)
		for (size_t j = 0; j < graymap.GetWidth(); ++j)
		{
			colormap(i, j) = ToRgbPixel(graymap(i, j));
		}
	return colormap;
}