#include "../inc/BitPixel.h"
#include "../inc/WritingError.h"
#include "../inc/ReadingError.h"

std::ostream& operator <<(std::ostream& output, const BitPixel& pixel)
{
	try
	{
		return output << pixel.isBlack;
	}
	catch (std::exception&)
	{
		throw WritingError("Error writing BitPixel to output.");
	}
}

std::istream& operator >>(std::istream& input, BitPixel& pixel)
{
	try
	{
		return input >> pixel.isBlack;
	}
	catch (std::exception&)
	{
		throw ReadingError("Error reading BitPixel from input.");
	}
}
