#pragma once
#include <vector>
#include "Image.h"
#include "RgbPixel.h"

using std::vector;

class PgmImage : public Image
{
	vector<vector<unsigned short>> graymap;

public:
	PgmImage(const ImageHeader& header, vector<vector<unsigned short>> graymap);
	const vector<vector<unsigned short>>& GetPixels() const { return graymap; }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;

private:
	vector<vector<char>> GraymapToBitmap();
	vector<vector<RgbPixel>> GraymapToColormap();
};
