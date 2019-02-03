#pragma once
#include <string>
#include <fstream>
#include "Image.h"
#include "PbmImage.h"
#include "PgmImage.h"
#include "PpmImage.h"

using std::string;
using std::shared_ptr;

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
	const ImageHeader header = imageToSave->GetHeader();
	auto pixels = std::dynamic_pointer_cast<T>(imageToSave)->GetPixels();
	for (auto i = 0; i < header.width; ++i)
	{
		for (auto j = 0; j < header.height; ++j)
		{
			targetFile << pixels.at(i).at(j) << ' ';
		}
		targetFile << '\n';
	}
}
