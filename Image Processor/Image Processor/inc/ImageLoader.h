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
	string sourceFilename;
	std::ifstream sourceFile;
	vector<string> comments;
	int width;
	int height;

public:
	ImageLoader();
	shared_ptr<Image> Load(const string& sourceFilename);

private:
	void OpenNewFile();
	shared_ptr<Image> LoadByFormat();
	shared_ptr<PbmImage> LoadPbm();
	shared_ptr<PgmImage> LoadPgm();
	shared_ptr<PpmImage> LoadPpm();
	vector<string> LoadComments();
	template <typename T>
	vector<vector<T>> LoadPixels();
};

template <typename T>
vector<vector<T>> ImageLoader::LoadPixels()
{
	auto pixels = vector<vector<T>>(width, vector<T>(height));
	for (auto i = 0; i < width; ++i)
		for (auto j = 0; j < height; ++j)
		{
			sourceFile >> pixels.at(i).at(j);
		}
	return pixels;
}
