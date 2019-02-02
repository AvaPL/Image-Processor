#pragma once
#include <vector>
#include "../inc/RgbPixel.h"

using std::vector;
using std::string;
using std::ofstream;

class PpmImage
{
	int width;
	int height;
	unsigned short maxColorValue;
	vector<vector<RgbPixel>> colormap;
	vector<string> comments;

public:
	PpmImage() : width(), height(), maxColorValue()
	//TODO: Make the constructor private.
	{
	};
	void Load(const string& sourceFilename);
	void Save(const string& targetFilename);

private:
	void LoadHeader(std::ifstream& sourceFile);
	void CheckFormat(std::ifstream& sourceFile) const;
	void LoadComments(std::ifstream& sourceFile);
	void LoadColormap(std::ifstream& sourceFile);

	void SaveHeader(ofstream& targetFile);
	void SaveComments(ofstream& targetFile);
	void SaveColormap(ofstream& targetFile);
};
