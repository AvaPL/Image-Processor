#pragma once
#include <iostream>

struct RgbPixel
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;

	explicit RgbPixel(const unsigned short red = 0, const unsigned short green = 0,
	                  const unsigned short blue = 0): red(red), green(green), blue(blue)
	{
	}

	class RgbPixelIterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = unsigned short;
		using difference_type = ptrdiff_t;
		using pointer = unsigned short *;
		using reference = unsigned short &;

		RgbPixelIterator(RgbPixel& rgbPixel, const int index) : rgbPixel(rgbPixel), index(index)
		{
		}

		RgbPixelIterator& operator++();
		RgbPixelIterator operator++(int);
		reference operator*() const;
		pointer operator->() const;
		bool operator==(const RgbPixelIterator& otherIterator) const;
		bool operator!=(const RgbPixelIterator& otherIterator) const;
	private:
		RgbPixel& rgbPixel;
		int index;
	};

	RgbPixelIterator begin() { return RgbPixelIterator(*this, 0); }
	RgbPixelIterator end();

	friend std::ostream& operator <<(std::ostream& output, const RgbPixel& pixel);
	friend std::istream& operator >>(std::istream& input, RgbPixel& pixel);
};
