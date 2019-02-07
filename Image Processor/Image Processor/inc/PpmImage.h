#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "RgbPixel.h"

using std::vector;

class PpmImage : public Image
{
	PixelMap<RgbPixel> colormap;

public:
	PpmImage(const ImageMeta& meta, PixelMap<RgbPixel> colormap);
	const PixelMap<RgbPixel>& GetPixels() const { return colormap; }
	int GetWidth() const override { return colormap.GetWidth(); }
	int GetHeight() const override { return colormap.GetHeight(); }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;
};
