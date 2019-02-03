#pragma once
#include <vector>
#include "Image.h"
#include "../inc/RgbPixel.h"

using std::vector;
using std::string;
using std::ofstream;

class PpmImage : public Image
{
	unsigned short maxColorValue;
	vector<vector<RgbPixel>> colormap;

public:
	PpmImage(const vector<string>& comments, int width, int height, unsigned short maxColorValue, vector<vector<RgbPixel>> colormap);
	void Save(const string& targetFilename) override;

private:
	void SaveHeader(ofstream& targetFile) override;
	void SavePixels(ofstream& targetFile) override;
};
