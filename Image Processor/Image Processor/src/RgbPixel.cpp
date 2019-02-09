#include "../inc/RgbPixel.h"

std::ostream& operator <<(std::ostream& output, const RgbPixel& pixel)
{
	return output << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}

std::istream& operator >>(std::istream& input, RgbPixel& pixel)
{
	return input >> pixel.red >> pixel.green >> pixel.blue;
}
