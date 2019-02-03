#include "../inc/PbmImage.h"
#include <fstream>
#include <string>
#include <utility>

using std::string;
using std::ifstream;
using std::ofstream;

PbmImage::PbmImage(const ImageHeader& header, vector<vector<char>> bitmap): Image(header), bitmap(std::move(bitmap))
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
	targetFile << header.width << ' ' << header.height << "\n";
}

void PbmImage::SavePixels(ofstream& targetFile)
{
	for (auto i = 0; i < header.width; ++i)
	{
		for (auto j = 0; j < header.height; ++j)
		{
			targetFile << bitmap.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
