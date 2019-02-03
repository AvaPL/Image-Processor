#include <fstream>
#include <string>
#include "../inc/PpmImage.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;

PpmImage::PpmImage(const vector<string>& comments, int width, int height, unsigned short maxColorValue,
                   vector<vector<RgbPixel>> colormap) : Image(comments, width, height), maxColorValue(maxColorValue),
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
	targetFile << width << ' ' << height << '\n' << maxColorValue << "\n";
}

void PpmImage::SavePixels(ofstream& targetFile)
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
