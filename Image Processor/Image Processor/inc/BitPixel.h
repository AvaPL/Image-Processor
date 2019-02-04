#pragma once
#include <fstream>

struct BitPixel
{
	bool isBlack;

	explicit BitPixel(const bool isBlack = false) : isBlack(isBlack)
	{
	}

	friend std::ostream& operator <<(std::ostream& output, const BitPixel& pixel);
	friend std::istream& operator >>(std::istream& input, BitPixel& pixel);
};
