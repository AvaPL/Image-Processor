#pragma once
#include <string>
#include <fstream>
#include "Image.h"
#include "PbmImage.h"
#include "PgmImage.h"
#include "PpmImage.h"

using std::string;
using std::shared_ptr;

//TODO: Split into interface and specialized savers for each format.

class ImageSaver
{
	shared_ptr<Image> imageToSave;
	std::ofstream targetFile;

public:
	ImageSaver();
	void Save(shared_ptr<Image> imageToSave, const string& targetFilename);

	static bool FileExists(const string& filename)
	{
		const std::ifstream file(filename);
		return static_cast<bool>(file);
	}

private:
	void SaveByFormat();
	void SavePbm();
	void SavePgm();
	void SavePpm();
	void SaveComments();
	template <typename T>
	void SavePixels();
};

template <typename T>
void ImageSaver::SavePixels()
{
	auto pixels = std::dynamic_pointer_cast<T>(imageToSave)->GetPixels();
	for (auto i = 0; i < imageToSave->GetHeight(); ++i)
	{
		for (auto j = 0; j < imageToSave->GetWidth(); ++j)
		{
			targetFile << pixels(i, j) << ' ';
		}
		targetFile << '\n';
	}
}
