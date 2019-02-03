#pragma once
#include <vector>
#include "Image.h"

using std::vector;

class PgmImage : public Image
{
	vector<vector<unsigned short>> graymap;

public:
	PgmImage(const ImageHeader& header, vector<vector<unsigned short>> graymap);
	const vector<vector<unsigned short>>& GetPixels() const { return graymap; }
};
