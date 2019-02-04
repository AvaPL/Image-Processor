#pragma once
#include <vector>
#include "Image.h"
#include "../inc/RgbPixel.h"

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
	vector<vector<char>> ColormapToBitmap();
	static char RgbPixelToBitValue(const RgbPixel& pixel); //TODO: Remove, add GrayPixel and BitPixel class with conversion.
	vector<vector<unsigned short>> ColormapToGraymap();
	static unsigned short RgbPixelToGrayValue(const RgbPixel& pixel); //TODO: Remove, add GrayPixel and BitPixel class with conversion.
};
