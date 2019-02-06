#pragma once
#include <utility>
#include "ImageMeta.h"

using std::shared_ptr;

class Image
{
protected:
	ImageMeta meta;

public:
	explicit Image(ImageMeta header) : meta(std::move(header))
	{
	}

	virtual ~Image() = 0;

	Format GetFormat() const { return meta.GetFormat(); }
	const vector<string>& GetComments() const { return meta.GetComments(); }
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	unsigned short GetMaxValue() { return meta.GetMaxValue(); }
	virtual shared_ptr<Image> ToPbm() = 0;
	virtual shared_ptr<Image> ToPgm() = 0;
	virtual shared_ptr<Image> ToPpm() = 0;

};
