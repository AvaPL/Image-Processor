#pragma once
#include <vector>
#include "Image.h"

using std::vector;
using std::string;
using std::ofstream;

class PbmImage : public Image
{
	vector<vector<char>> bitmap;

public:
	PbmImage(const ImageHeader& header, vector<vector<char>> bitmap);
	void Save(const string& targetFilename) override;

private:
	void SaveHeader(ofstream& targetFile) override;
	void SavePixels(ofstream& targetFile) override;
};
