#include "../inc/PgmImage.h"
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;

PgmImage::PgmImage(const ImageHeader& header, vector<vector<unsigned short>> graymap): Image(header),
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
	targetFile << header.width << ' ' << header.height << '\n' << header.maxValue << "\n";
}

void PgmImage::SavePixels(ofstream& targetFile)
{
	for (auto i = 0; i < header.width; ++i)
	{
		for (auto j = 0; j < header.height; ++j)
		{
			targetFile << graymap.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
