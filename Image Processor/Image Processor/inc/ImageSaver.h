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

	static bool FileExists(const string& filename);

private:
	void SafeSave(shared_ptr<Image> imageToSave, const string& targetFilename);
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
	for (const auto& element : pixels)
		targetFile << element << ' ';
}
