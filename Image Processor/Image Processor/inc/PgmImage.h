#pragma once
#include <vector>
#include "Image.h"
#include "GrayPixel.h"
#include "BitPixel.h"
#include "RgbPixel.h"

using std::vector;

class PgmImage : public Image
{
	vector<vector<GrayPixel>> graymap;

public:
	PgmImage(const ImageHeader& header, vector<vector<GrayPixel>> graymap);
	const vector<vector<GrayPixel>>& GetPixels() const { return graymap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	vector<vector<BitPixel>> GraymapToBitmap();
	vector<vector<RgbPixel>> GraymapToColormap();
};
