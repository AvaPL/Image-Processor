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
	void Load(const string& sourceFilename) override;
	void Save(const string& targetFilename) override;

private:
	void LoadHeader(std::ifstream& sourceFile) override;
	void CheckFormat(std::ifstream& sourceFile) const override;
	void LoadPixels(std::ifstream& sourceFile) override;

	void SaveHeader(ofstream& targetFile) override;
	void SavePixels(ofstream& targetFile) override;
};
