#include "../inc/RgbPixel.h"
#include <string>

RgbPixel::RgbPixelIterator& RgbPixel::RgbPixelIterator::operator++()
{
	++index;
	return *this;
}

RgbPixel::RgbPixelIterator RgbPixel::RgbPixelIterator::operator++(int)
{
	const int previousIndex = index;
	++index;
	return RgbPixelIterator(rgbPixel, previousIndex);
}

RgbPixel::RgbPixelIterator::reference RgbPixel::RgbPixelIterator::operator*() const
{
	switch (index)
	{
	case 0:
		return rgbPixel.red;
	case 1:
		return rgbPixel.green;
	case 2:
		return rgbPixel.blue;
	default:
		throw std::out_of_range("Error dereferencing RgbPixel channel value.");
	}
}

RgbPixel::RgbPixelIterator::pointer RgbPixel::RgbPixelIterator::operator->() const
{
	//Returns adress of dereferenced channel value.
	return &**this;
}

bool RgbPixel::RgbPixelIterator::operator==(const RgbPixelIterator& otherIterator) const
{
	return index == otherIterator.index;
}

bool RgbPixel::RgbPixelIterator::operator!=(const RgbPixelIterator& otherIterator) const
{
	return index != otherIterator.index;
}

RgbPixel::RgbPixelIterator RgbPixel::end()
{
	//Returns an iterator with index next to the last possible index.
	return RgbPixelIterator(*this, 3);
}

std::ostream& operator <<(std::ostream& output, const RgbPixel& pixel)
{
	return output << pixel.red << ' ' << pixel.green << ' ' << pixel.blue;
}

std::istream& operator >>(std::istream& input, RgbPixel& pixel)
{
	return input >> pixel.red >> pixel.green >> pixel.blue;
}