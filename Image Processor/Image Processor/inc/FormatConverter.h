#pragma once
#include "BitPixel.h"
#include "GrayPixel.h"
#include "RgbPixel.h"
#include "PixelMap.h"

class FormatConverter
{
	FormatConverter() = default;

public:
	static BitPixel ToBitPixel(const GrayPixel& grayPixel, const unsigned short maxGrayValue);
	static BitPixel ToBitPixel(const RgbPixel& rgbPixel, const unsigned short maxColorValue);
	static GrayPixel ToGrayPixel(const BitPixel& bitPixel, const unsigned short maxGrayValue);
	static GrayPixel ToGrayPixel(const RgbPixel& rgbPixel);
	static RgbPixel ToRgbPixel(const BitPixel& bitPixel, const unsigned short maxColorValue);
	static RgbPixel ToRgbPixel(const GrayPixel& grayPixel);
	static PixelMap<BitPixel> ToBitmap(const PixelMap<GrayPixel>& graymap, const unsigned short maxGrayValue);
	static PixelMap<BitPixel> ToBitmap(const PixelMap<RgbPixel>& colormap, const unsigned short maxColorValue);
	static PixelMap<GrayPixel> ToGraymap(const PixelMap<BitPixel>& bitmap);
	static PixelMap<GrayPixel> ToGraymap(const PixelMap<RgbPixel>& colormap);
	static PixelMap<RgbPixel> ToColormap(const PixelMap<BitPixel>& bitmap);
	static PixelMap<RgbPixel> ToColormap(const PixelMap<GrayPixel>& graymap);
};
