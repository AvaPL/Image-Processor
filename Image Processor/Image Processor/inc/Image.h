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
	unsigned short GetMaxValue() const { return meta.GetMaxValue(); }
	virtual shared_ptr<Image> ToPbm() = 0;
	virtual shared_ptr<Image> ToPgm() = 0;
	virtual shared_ptr<Image> ToPpm() = 0;
	virtual shared_ptr<Image> Negative() = 0;
	virtual shared_ptr<Image> Tresholding(const unsigned short treshold) = 0;
	virtual shared_ptr<Image> BlackTresholding(const unsigned short treshold) = 0;
	virtual shared_ptr<Image> WhiteTresholding(const unsigned short treshold) = 0;
	virtual shared_ptr<Image> GammaCorrection(double gamma) = 0;
	virtual shared_ptr<Image> LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold) = 0;
	virtual shared_ptr<Image> Contouring() = 0;
	virtual shared_ptr<Image> HorizontalBlur() = 0;
	virtual shared_ptr<Image> VerticalBlur() = 0;
	virtual shared_ptr<Image> HistogramStretching() = 0;
};
