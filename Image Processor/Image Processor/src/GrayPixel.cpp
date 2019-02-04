#include <iostream>
#include "../inc/GrayPixel.h"

std::ostream& operator<<(std::ostream& output, const GrayPixel& pixel)
{
	return output << pixel.value;
}

std::istream& operator>>(std::istream& input, GrayPixel& pixel)
{
	return input >> pixel.value;
}
