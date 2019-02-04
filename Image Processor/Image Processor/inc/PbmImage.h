#pragma once
#include <vector>
#include "Image.h"
#include "BitPixel.h"
#include "GrayPixel.h"
#include "RgbPixel.h"

using std::vector;
using std::shared_ptr;

class PbmImage : public Image
{
	vector<vector<BitPixel>> bitmap;

public:
	PbmImage(const ImageHeader& header, vector<vector<BitPixel>> bitmap);
	const vector<vector<BitPixel>>& GetPixels() const { return bitmap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	vector<vector<GrayPixel>> BitmapToGraymap();
	vector<vector<RgbPixel>> BitmapToColormap();
};
