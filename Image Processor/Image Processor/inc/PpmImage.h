#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "RgbPixel.h"
#include "BitPixel.h"
#include "GrayPixel.h"

using std::vector;

class PpmImage : public Image
{
	PixelMap<RgbPixel> colormap;

public:
	PpmImage(const ImageHeader& header, PixelMap<RgbPixel> colormap);
	const PixelMap<RgbPixel>& GetPixels() const { return colormap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	PixelMap<BitPixel> ColormapToBitmap();
	PixelMap<GrayPixel> ColormapToGraymap();
};
