#pragma once
#include <vector>
#include <string>
#include <fstream>

using std::string;

//TODO: Make all constructors private, create object only by returning through Load() (remove void).

class Image
{
protected:
	int width;
	int height;
	std::vector<string> comments;

	virtual void LoadHeader(std::ifstream& sourceFile) = 0;
	virtual void CheckFormat(std::ifstream& sourceFile) const = 0;
	virtual void LoadComments(std::ifstream& sourceFile);
	virtual void LoadPixels(std::ifstream& sourceFile) = 0;

	virtual void SaveHeader(std::ofstream& targetFile) = 0;
	virtual void SaveComments(std::ofstream& targetFile);
	virtual void SavePixels(std::ofstream& targetFile) = 0;
public:
	virtual ~Image() = default;

	Image() : width(), height()
	{
	};
	virtual void Load(const string& sourceFilename) = 0;
	virtual void Save(const string& targetFilename) = 0;
};
