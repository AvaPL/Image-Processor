#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "GrayPixel.h"
#include "BitPixel.h"
#include "RgbPixel.h"

using std::vector;

class PgmImage : public Image
{
	PixelMap<GrayPixel> graymap;

public:
	PgmImage(const ImageHeader& header, PixelMap<GrayPixel> graymap);
	const PixelMap<GrayPixel>& GetPixels() const { return graymap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	PixelMap<BitPixel> GraymapToBitmap();
	PixelMap<RgbPixel> GraymapToColormap();
};
