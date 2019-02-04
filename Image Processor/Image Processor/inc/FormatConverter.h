#pragma once
#include "BitPixel.h"
#include "GrayPixel.h"
#include "RgbPixel.h"

class FormatConverter
{
	FormatConverter() = default;

public:
	static BitPixel ToBitPixel(GrayPixel grayPixel, const unsigned short maxGrayValue);
	static BitPixel ToBitPixel(RgbPixel rgbPixel, const unsigned short maxColorValue);
	static GrayPixel ToGrayPixel(BitPixel bitPixel, const unsigned short maxGrayValue);
	static GrayPixel ToGrayPixel(RgbPixel rgbPixel);
	static RgbPixel ToRgbPixel(BitPixel bitPixel, const unsigned short maxColorValue);
	static RgbPixel ToRgbPixel(GrayPixel grayPixel);
};