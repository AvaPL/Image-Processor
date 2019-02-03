#pragma once
#include <vector>
#include <string>
#include <fstream>

using std::string;
using std::vector;

class Image
{
protected:
	int width;
	int height;
	vector<string> comments;

	virtual void SaveHeader(std::ofstream& targetFile) = 0;
	virtual void SaveComments(std::ofstream& targetFile);
	virtual void SavePixels(std::ofstream& targetFile) = 0;

public:
	Image(vector<string> comments, int width, int height);
	virtual ~Image() = default;

	virtual void Save(const string& targetFilename) = 0;
};
