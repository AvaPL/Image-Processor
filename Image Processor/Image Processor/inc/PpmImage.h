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
};
