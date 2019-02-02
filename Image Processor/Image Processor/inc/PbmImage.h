#pragma once
#include <vector>

using std::vector;
using std::string;
using std::ofstream;

class PbmImage
{
	int width, height;
	vector<vector<char>> bitmap;
	vector<string> comments;

public:
	PbmImage() : width(), height() //TODO: Make constructor private.
	{
	};
	void Load(const string& sourceFilename);
	void Save(const string& targetFilename);

private:
	void LoadHeader(std::ifstream& sourceFile);
	void CheckFormat(std::ifstream& sourceFile) const;
	void LoadComments(std::ifstream& sourceFile);
	void LoadBitmap(std::ifstream& sourceFile);

	void SaveHeader(ofstream& targetFile);
	void SaveComments(ofstream& targetFile);
	void SaveBitmap(ofstream& targetFile);
};
