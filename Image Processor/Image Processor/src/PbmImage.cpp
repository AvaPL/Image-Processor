#include "../inc/PbmImage.h"
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

void PbmImage::Load(const string& sourceFilename)
{
	ifstream sourceFile(sourceFilename);
	sourceFile.exceptions(std::ios::failbit | std::ios::badbit);
	LoadHeader(sourceFile);
	LoadBitmap(sourceFile);
}

void PbmImage::LoadHeader(ifstream& sourceFile)
{
	CheckFormat(sourceFile);
	LoadComments(sourceFile);
	sourceFile >> width >> height;
}

void PbmImage::CheckFormat(ifstream& sourceFile) const
{
	string buffer;
	getline(sourceFile, buffer);
	if (buffer != "P1")
		sourceFile.setstate(std::ios::badbit);
}

// void PbmImage::LoadComments(ifstream& sourceFile)
// {
// 	string buffer;
// 	while (sourceFile.peek() == '#')
// 	{
// 		getline(sourceFile, buffer);
// 		comments.push_back(buffer);
// 	}
// }

void PbmImage::LoadBitmap(ifstream& sourceFile)
{
	bitmap = vector<vector<char>>(width, vector<char>(height));
	for (auto i = 0; i < width; ++i)
		for (auto j = 0; j < height; ++j)
		{
			sourceFile >> bitmap.at(i).at(j);
		}
}

void PbmImage::Save(const string& targetFilename) //TODO: Add a method to check if file already exists.
{
	ofstream targetFile(targetFilename);
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
	SaveHeader(targetFile);
	SaveBitmap(targetFile);
}

void PbmImage::SaveHeader(ofstream& targetFile)
{
	targetFile << "P1\n";
	SaveComments(targetFile);
	targetFile << width << ' ' << height << "\n";
}

// void PbmImage::SaveComments(ofstream& targetFile)
// {
// 	for (const auto& element : comments)
// 	{
// 		targetFile << element << '\n';
// 	}
// }

void PbmImage::SaveBitmap(ofstream& targetFile)
{
	for (auto i = 0; i < width; ++i)
	{
		for (auto j = 0; j < height; ++j)
		{
			targetFile << bitmap.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
