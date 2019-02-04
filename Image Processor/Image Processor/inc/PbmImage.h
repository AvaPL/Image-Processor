#pragma once
#include <vector>
#include "Image.h"
#include "RgbPixel.h"

using std::vector;
using std::shared_ptr;

class PbmImage : public Image
{
	vector<vector<char>> bitmap;

public:
	PbmImage(const ImageHeader& header, vector<vector<char>> bitmap);
	const vector<vector<char>>& GetPixels() const { return bitmap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	vector<vector<unsigned short>> BitmapToGraymap();
	vector<vector<RgbPixel>> BitmapToColormap();
};
