#include "../inc/PbmImage.h"
#include <fstream>
#include <string>
#include <utility>

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

PbmImage::PbmImage(const vector<string>& comments, const int width, const int height, vector<vector<char>> bitmap):
	Image(comments, width, height),
	bitmap(std::move(bitmap))
{
}

void PbmImage::Save(const string& targetFilename) //TODO: Add a method to check if file already exists.
{
	ofstream targetFile(targetFilename);
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
	SaveHeader(targetFile);
	SavePixels(targetFile);
}

void PbmImage::SaveHeader(ofstream& targetFile)
{
	targetFile << "P1\n";
	SaveComments(targetFile);
	targetFile << width << ' ' << height << "\n";
}

void PbmImage::SavePixels(ofstream& targetFile)
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
