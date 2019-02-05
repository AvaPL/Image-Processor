#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "BitPixel.h"
#include "GrayPixel.h"
#include "RgbPixel.h"

using std::vector;
using std::shared_ptr;

class PbmImage : public Image
{
	PixelMap<BitPixel> bitmap;

public:
	PbmImage(const ImageHeader& header, PixelMap<BitPixel> bitmap);
	const PixelMap<BitPixel>& GetPixels() const { return bitmap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	PixelMap<GrayPixel> BitmapToGraymap();
	PixelMap<RgbPixel> BitmapToColormap();
};
