#include "../inc/FormatConverter.h"

BitPixel FormatConverter::ToBitPixel(GrayPixel grayPixel, const unsigned short maxGrayValue)
{
	const bool isBlack = grayPixel.value <= maxGrayValue / 2;
	return BitPixel(isBlack);
}

BitPixel FormatConverter::ToBitPixel(RgbPixel rgbPixel, const unsigned short maxColorValue)
{
	const auto grayValue = ToGrayPixel(rgbPixel).value;
	const bool isBlack = grayValue <= maxColorValue / 2;
	return BitPixel(isBlack);
}

GrayPixel FormatConverter::ToGrayPixel(BitPixel bitPixel, const unsigned short maxGrayValue)
{
	const unsigned short grayValue = bitPixel.isBlack ? 0 : maxGrayValue;
	return GrayPixel(grayValue);
}

GrayPixel FormatConverter::ToGrayPixel(RgbPixel rgbPixel)
{
	return GrayPixel((rgbPixel.red + rgbPixel.green + rgbPixel.blue) / 3);
}

RgbPixel FormatConverter::ToRgbPixel(BitPixel bitPixel, const unsigned short maxColorValue)
{
	const unsigned short colorChannelValue = ToGrayPixel(bitPixel, maxColorValue).value;
	return RgbPixel(colorChannelValue, colorChannelValue, colorChannelValue);
}

RgbPixel FormatConverter::ToRgbPixel(GrayPixel grayPixel)
{
	return RgbPixel(grayPixel.value, grayPixel.value, grayPixel.value);
}
