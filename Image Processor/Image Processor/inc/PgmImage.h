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
	PgmImage() : maxGrayValue()
	{
	};
	void Load(const string& sourceFilename) override;
	void Save(const string& targetFilename) override;

private:
	void LoadHeader(std::ifstream& sourceFile);
	void CheckFormat(std::ifstream& sourceFile) const;
	void LoadGraymap(std::ifstream& sourceFile);

	void SaveHeader(ofstream& targetFile);
	void SaveGraymap(ofstream& targetFile);
};
