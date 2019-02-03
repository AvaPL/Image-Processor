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
	PpmImage() : maxColorValue()
	{
	};
	void Load(const string& sourceFilename) override;
	void Save(const string& targetFilename) override;

private:
	void LoadHeader(std::ifstream& sourceFile);
	void CheckFormat(std::ifstream& sourceFile) const;
	void LoadColormap(std::ifstream& sourceFile);

	void SaveHeader(ofstream& targetFile);
	void SaveColormap(ofstream& targetFile);
};
