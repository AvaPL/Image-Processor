#pragma once
#include <iostream>

struct GrayPixel
{
	unsigned short value;

	explicit GrayPixel(const unsigned short value = 0) : value(value)
	{
	}

	friend std::ostream& operator <<(std::ostream& output, const GrayPixel& pixel);
	friend std::istream& operator >>(std::istream& input, GrayPixel& pixel);
};
