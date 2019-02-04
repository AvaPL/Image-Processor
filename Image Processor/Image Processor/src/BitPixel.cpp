#include <iostream>
#include "../inc/BitPixel.h"

std::ostream& operator <<(std::ostream& output, const BitPixel& pixel)
{
	return output << pixel.isBlack;
}

std::istream& operator >>(std::istream& input, BitPixel& pixel)
{
	return input >> pixel.isBlack;
}
