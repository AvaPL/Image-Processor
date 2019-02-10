#include "../inc/GrayPixel.h"
#include "../inc/WritingError.h"
#include "../inc/ReadingError.h"

std::ostream& operator<<(std::ostream& output, const GrayPixel& pixel)
{
	try
	{
		return output << pixel.value;
	}
	catch (std::exception&)
	{
		throw WritingError("Error writing GrayPixel to output.");
	}
}

std::istream& operator>>(std::istream& input, GrayPixel& pixel)
{
	try
	{
		return input >> pixel.value;
	}
	catch (std::exception&)
	{
		throw ReadingError("Error reading GrayPixel from input.");
	}
}
