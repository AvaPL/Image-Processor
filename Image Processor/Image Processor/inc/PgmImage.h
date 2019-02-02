#pragma once
#include <vector>

using std::vector;
using std::string;
using std::ofstream;

class PgmImage
{
	int width;
	int height;
	unsigned short maxGrayValue;
	vector<vector<unsigned short>> graymap;
	vector<string> comments;

public:
	PgmImage() : width(), height(), maxGrayValue()
	//TODO: Make the constructor private.
	{
	};
	void Load(const string& sourceFilename);
	void Save(const string& targetFilename);

private:
	void LoadHeader(std::ifstream& sourceFile);
	void CheckFormat(std::ifstream& sourceFile) const;
	void LoadComments(std::ifstream& sourceFile);
	void LoadGraymap(std::ifstream& sourceFile);

	void SaveHeader(ofstream& targetFile);
	void SaveComments(ofstream& targetFile);
	void SaveGraymap(ofstream& targetFile);
};
