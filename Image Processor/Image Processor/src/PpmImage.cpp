#include <fstream>
#include <string>
#include "../inc/PpmImage.h"


using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

void PpmImage::Load(const string& sourceFilename)
{
	ifstream sourceFile(sourceFilename);
	sourceFile.exceptions(std::ios::failbit | std::ios::badbit);
	LoadHeader(sourceFile);
	LoadColormap(sourceFile);
}

void PpmImage::LoadHeader(ifstream& sourceFile)
{
	CheckFormat(sourceFile);
	LoadComments(sourceFile);
	sourceFile >> width >> height >> maxColorValue;
}

void PpmImage::CheckFormat(ifstream& sourceFile) const
{
	string buffer;
	getline(sourceFile, buffer);
	if (buffer != "P3")
		sourceFile.setstate(std::ios::badbit);
}

void PpmImage::LoadComments(ifstream& sourceFile)
{
	string buffer;
	while (sourceFile.peek() == '#')
	{
		getline(sourceFile, buffer);
		comments.push_back(buffer);
	}
}

void PpmImage::LoadColormap(ifstream& sourceFile) //TODO: Add a method to check if values are lower than maxColorValue.
{
	colormap = vector<vector<RgbPixel>>(width, vector<RgbPixel>(height));
	for (auto i = 0; i < width; ++i)
		for (auto j = 0; j < height; ++j)
		{
			sourceFile >> colormap.at(i).at(j);
		}
}

void PpmImage::Save(const string& targetFilename) //TODO: Add a method to check if file already exists.
{
	ofstream targetFile(targetFilename);
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
	SaveHeader(targetFile);
	SaveColormap(targetFile);
}

void PpmImage::SaveHeader(ofstream& targetFile)
{
	targetFile << "P3\n";
	SaveComments(targetFile);
	targetFile << width << ' ' << height << '\n' << maxColorValue << "\n";
}

void PpmImage::SaveComments(ofstream& targetFile)
{
	for (const auto& element : comments)
	{
		targetFile << element << '\n';
	}
}

void PpmImage::SaveColormap(ofstream& targetFile)
{
	for (auto i = 0; i < width; ++i)
	{
		for (auto j = 0; j < height; ++j)
		{
			targetFile << colormap.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
