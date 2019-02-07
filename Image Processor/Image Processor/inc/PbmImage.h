#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "BitPixel.h"

using std::vector;
using std::shared_ptr;

//TODO: Move converters to FormatConverter class.

class PbmImage : public Image
{
	PixelMap<BitPixel> bitmap;

public:
	PbmImage(const ImageMeta& meta, PixelMap<BitPixel> bitmap);
	const PixelMap<BitPixel>& GetPixels() const { return bitmap; }
	int GetWidth() const override { return bitmap.GetWidth(); }
	int GetHeight() const override { return bitmap.GetHeight(); }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;
	
};
