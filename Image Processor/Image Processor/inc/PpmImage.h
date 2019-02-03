#pragma once
#include <vector>
#include "Image.h"
#include "../inc/RgbPixel.h"

using std::vector;
using std::string;
using std::ofstream;

class PpmImage : public Image
{
	vector<vector<RgbPixel>> colormap;

public:
	PpmImage(const ImageHeader& header, vector<vector<RgbPixel>> colormap);
	void Save(const string& targetFilename) override;

private:
	void SaveHeader(ofstream& targetFile) override;
	void SavePixels(ofstream& targetFile) override;
};
