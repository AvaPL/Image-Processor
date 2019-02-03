#pragma once
#include <vector>
#include "Image.h"

using std::vector;
using std::string;
using std::ofstream;

class PgmImage : public Image
{
	vector<vector<unsigned short>> graymap;

public:
	PgmImage(const ImageHeader& header, vector<vector<unsigned short>> graymap);
	void Save(const string& targetFilename) override;

private:
	void SaveHeader(ofstream& targetFile) override;
	void SavePixels(ofstream& targetFile) override;
};
