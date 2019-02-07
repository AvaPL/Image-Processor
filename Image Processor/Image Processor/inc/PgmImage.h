#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "GrayPixel.h"

using std::vector;

//TODO: Move converters to FormatConverter class.

class PgmImage : public Image
{
	PixelMap<GrayPixel> graymap;

public:
	PgmImage(const ImageMeta& meta, PixelMap<GrayPixel> graymap);
	const PixelMap<GrayPixel>& GetPixels() const { return graymap; }
	int GetWidth() const override { return graymap.GetWidth(); }
	int GetHeight() const override { return graymap.GetHeight(); }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;
};
