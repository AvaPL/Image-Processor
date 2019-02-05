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
	PixelMap<T> LoadPixels(const ImageHeader& header);
};

template <typename T>
PixelMap<T> ImageLoader::LoadPixels(const ImageHeader& header)
{
	auto pixels = PixelMap<T>(header.width, header.height);
	for (auto i = 0; i < header.height; ++i)
		for (auto j = 0; j < header.width; ++j)
		{
			sourceFile >> pixels(i, j);
		}
	return pixels;
}
