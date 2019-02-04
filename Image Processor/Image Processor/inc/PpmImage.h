#pragma once
#include <vector>
#include "Image.h"
#include "RgbPixel.h"
#include "BitPixel.h"
#include "GrayPixel.h"

using std::vector;

class PpmImage : public Image
{
	vector<vector<RgbPixel>> colormap;

public:
	PpmImage(const ImageHeader& header, vector<vector<RgbPixel>> colormap);
	const vector<vector<RgbPixel>>& GetPixels() const { return colormap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	vector<vector<BitPixel>> ColormapToBitmap();
	vector<vector<GrayPixel>> ColormapToGraymap();
};
