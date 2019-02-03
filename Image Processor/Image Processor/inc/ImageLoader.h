#pragma once
#include <string>
#include <fstream>
#include "Image.h"
#include "PbmImage.h"
#include "PgmImage.h"
#include "PpmImage.h"

using std::string;
using std::shared_ptr;

class ImageLoader
{
	std::ifstream sourceFile;

public:
	ImageLoader();
	shared_ptr<Image> Load(const string& sourceFilename);

private:
	shared_ptr<Image> LoadByFormat();
	shared_ptr<PbmImage> LoadPbm();
	shared_ptr<PgmImage> LoadPgm();
	shared_ptr<PpmImage> LoadPpm();
	vector<string> LoadComments();
	template <typename T>
	vector<vector<T>> LoadPixels(const ImageHeader& header);
};

template <typename T>
vector<vector<T>> ImageLoader::LoadPixels(const ImageHeader& header)
{
	auto pixels = vector<vector<T>>(header.width, vector<T>(header.height));
	for (auto i = 0; i < header.width; ++i)
		for (auto j = 0; j < header.height; ++j)
		{
			sourceFile >> pixels.at(i).at(j);
		}
	return pixels;
}
