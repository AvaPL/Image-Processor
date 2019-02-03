#include "../inc/PgmImage.h"
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

void PgmImage::Load(const string& sourceFilename)
{
	ifstream sourceFile(sourceFilename);
	sourceFile.exceptions(std::ios::failbit | std::ios::badbit);
	LoadHeader(sourceFile);
	LoadGraymap(sourceFile);
}

void PgmImage::LoadHeader(ifstream& sourceFile)
{
	CheckFormat(sourceFile);
	LoadComments(sourceFile);
	sourceFile >> width >> height >> maxGrayValue;
}

void PgmImage::CheckFormat(ifstream& sourceFile) const
{
	string buffer;
	getline(sourceFile, buffer);
	if (buffer != "P2")
		sourceFile.setstate(std::ios::badbit);
}

// void PgmImage::LoadComments(ifstream& sourceFile)
// {
// 	string buffer;
// 	while (sourceFile.peek() == '#')
// 	{
// 		getline(sourceFile, buffer);
// 		comments.push_back(buffer);
// 	}
// }

void PgmImage::LoadGraymap(ifstream& sourceFile) //TODO: Add a method to check if values are lower than maxGrayValue.
{
	graymap = vector<vector<unsigned short>>(width, vector<unsigned short>(height));
	for (auto i = 0; i < width; ++i)
		for (auto j = 0; j < height; ++j)
		{
			sourceFile >> graymap.at(i).at(j);
		}
}

void PgmImage::Save(const string& targetFilename) //TODO: Add a method to check if file already exists.
{
	ofstream targetFile(targetFilename);
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
	SaveHeader(targetFile);
	SaveGraymap(targetFile);
}

void PgmImage::SaveHeader(ofstream& targetFile)
{
	targetFile << "P2\n";
	SaveComments(targetFile);
	targetFile << width << ' ' << height << '\n' << maxGrayValue << "\n";
}

// void PgmImage::SaveComments(ofstream& targetFile)
// {
// 	for (const auto& element : comments)
// 	{
// 		targetFile << element << '\n';
// 	}
// }

void PgmImage::SaveGraymap(ofstream& targetFile)
{
	for (auto i = 0; i < width; ++i)
	{
		for (auto j = 0; j < height; ++j)
		{
			targetFile << graymap.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
