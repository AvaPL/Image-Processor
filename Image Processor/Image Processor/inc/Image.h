#pragma once
#include <utility>
#include "ImageHeader.h"

class Image
{
protected:
	ImageHeader header;

public:
	explicit Image(ImageHeader header) : header(std::move(header))
	{
	}

	virtual ~Image() = default;

	virtual const ImageHeader& GetHeader() const { return header; }
};
