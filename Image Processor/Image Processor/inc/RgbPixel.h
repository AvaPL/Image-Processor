#pragma once

struct RgbPixel
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;

	RgbPixel(): red(), green(), blue()
	{
	}

	friend std::ostream& operator <<(std::ostream& output, const RgbPixel& pixel);
	friend std::istream& operator >>(std::istream& input, RgbPixel& pixel);
};
