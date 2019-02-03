#include <fstream>
#include <string>
#include "../inc/PpmImage.h"

using std::string;
using std::ifstream;
using std::ofstream;

PpmImage::PpmImage(const ImageHeader& header, vector<vector<RgbPixel>> colormap) : Image(header),
                                                                                   colormap(std::move(colormap))
{
}

void PpmImage::Save(const string& targetFilename) //TODO: Add a method to check if file already exists.
{
	ofstream targetFile(targetFilename);
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
	SaveHeader(targetFile);
	SavePixels(targetFile);
}

void PpmImage::SaveHeader(ofstream& targetFile)
{
	targetFile << "P3\n";
	SaveComments(targetFile);
	targetFile << header.width << ' ' << header.height << '\n' << header.maxValue << "\n";
}

void PpmImage::SavePixels(ofstream& targetFile)
{
	for (auto i = 0; i < header.width; ++i)
	{
		for (auto j = 0; j < header.height; ++j)
		{
			targetFile << colormap.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
