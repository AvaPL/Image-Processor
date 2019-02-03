#include "../inc/PgmImage.h"
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

PgmImage::PgmImage(const vector<string>& comments, const int width, const int height, const unsigned short maxGrayValue,
                   vector<vector<unsigned short>> graymap): Image(comments, width, height), maxGrayValue(maxGrayValue),
                                                            graymap(std::move(graymap))
{
}

void PgmImage::Save(const string& targetFilename) //TODO: Add a method to check if file already exists.
{
	ofstream targetFile(targetFilename);
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
	SaveHeader(targetFile);
	SavePixels(targetFile);
}

void PgmImage::SaveHeader(ofstream& targetFile)
{
	targetFile << "P2\n";
	SaveComments(targetFile);
	targetFile << width << ' ' << height << '\n' << maxGrayValue << "\n";
}

void PgmImage::SavePixels(ofstream& targetFile)
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
