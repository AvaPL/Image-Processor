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

	virtual void LoadComments(std::ifstream& sourceFile);
	virtual void SaveComments(std::ofstream& targetFile);

public:
	virtual ~Image() = default;

	Image() : width(), height()
	{
	};
	virtual void Load(const string& sourceFilename) = 0;
	virtual void Save(const string& targetFilename) = 0;
};
