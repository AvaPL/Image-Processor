#pragma once
#include <vector>
#include "Image.h"

using std::vector;

class PbmImage : public Image
{
	vector<vector<char>> bitmap;

public:
	PbmImage(const ImageHeader& header, vector<vector<char>> bitmap);
	const vector<vector<char>>& GetPixels() const { return bitmap; }
};
