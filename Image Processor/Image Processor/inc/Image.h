#pragma once
#include <utility>
#include "ImageHeader.h"

using std::shared_ptr;

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
	virtual shared_ptr<Image> ToPbm() = 0;
	virtual shared_ptr<Image> ToPgm() = 0;
	virtual shared_ptr<Image> ToPpm() = 0;

protected:
	ImageHeader GetPbmHeader() const;
	ImageHeader GetPgmHeader() const;
	ImageHeader GetPpmHeader() const;
};
