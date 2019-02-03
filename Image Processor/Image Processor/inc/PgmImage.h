#pragma once
#include <vector>
#include "Image.h"

using std::vector;
using std::string;
using std::ofstream;

class PgmImage : public Image
{
	unsigned short maxGrayValue;
	vector<vector<unsigned short>> graymap;

public:
	PgmImage(const vector<string>& comments, int width, int height, unsigned short maxGrayValue, vector<vector<unsigned short>> graymap);
	void Save(const string& targetFilename) override;

private:
	void SaveHeader(ofstream& targetFile) override;
	void SavePixels(ofstream& targetFile) override;
};
