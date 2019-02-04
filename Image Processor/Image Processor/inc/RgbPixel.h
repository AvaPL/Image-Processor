#pragma once
#include <fstream>

struct RgbPixel
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;

	explicit RgbPixel(const unsigned short red = 0, const unsigned short green = 0,
	                  const unsigned short blue = 0): red(red), green(green), blue(blue)
	{
	}

	friend std::ostream& operator <<(std::ostream& output, const RgbPixel& pixel);
	friend std::istream& operator >>(std::istream& input, RgbPixel& pixel);
};
