#pragma once
#include <utility>
#include "ImageHeader.h"

using std::shared_ptr;

class Image
{
protected:
	ImageHeader header;

	ImageHeader GetPbmHeader() const;
	ImageHeader GetPgmHeader(const unsigned short maxGrayValue) const;
	ImageHeader GetPpmHeader(const unsigned short maxColorValue) const;

public:
	explicit Image(ImageHeader header) : header(std::move(header))
	{
	}

	virtual ~Image() = 0;

	virtual const ImageHeader& GetHeader() const { return header; }
	virtual shared_ptr<Image> ToPbm() = 0;
	virtual shared_ptr<Image> ToPgm() = 0;
	virtual shared_ptr<Image> ToPpm() = 0;

};
