#pragma once
#include <string>
#include <fstream>
#include "Image.h"
#include "PbmImage.h"
#include "PgmImage.h"
#include "PpmImage.h"

using std::string;
using std::shared_ptr;

//TODO: Split into interface and specialized loaders for each format.

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
	void LoadMaxValue(ImageMeta& meta);
	void LoadComments(ImageMeta& meta);
	template <typename T>
	PixelMap<T> LoadPixelMap(size_t width, size_t height);
};

template <typename T>
PixelMap<T> ImageLoader::LoadPixelMap(size_t width, size_t height)
{
	auto pixels = PixelMap<T>(width, height);
	for (auto& element : pixels)
	{
		sourceFile >> element;
	}
	return pixels;
}
