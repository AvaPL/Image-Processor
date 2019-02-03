#include "../inc/ImageLoader.h"

using std::shared_ptr;

ImageLoader::ImageLoader()
{
	sourceFile.exceptions(std::ios::failbit | std::ios::badbit);
}

shared_ptr<Image> ImageLoader::Load(const string& sourceFilename)
{
	this->sourceFilename = sourceFilename;
	OpenNewFile();
	return LoadByFormat();
}

void ImageLoader::OpenNewFile()
{
	if (sourceFile.is_open())
		sourceFile.close();
	sourceFile.open(sourceFilename);
}

shared_ptr<Image> ImageLoader::LoadByFormat()
{
	string buffer;
	getline(sourceFile, buffer);
	if (buffer == "P1")
		return LoadPbm();
	else if (buffer == "P2")
		return LoadPgm();
	else if (buffer == "P3")
		return LoadPpm();
	else
	{
		sourceFile.setstate(std::ios::badbit);
		return nullptr;
	}
}

shared_ptr<PbmImage> ImageLoader::LoadPbm()
{
	comments = LoadComments();
	sourceFile >> width >> height;
	auto pixels = LoadPixels<char>();
	return std::make_shared<PbmImage>(comments, width, height, pixels);
}

shared_ptr<PgmImage> ImageLoader::LoadPgm()
{
	comments = LoadComments();
	unsigned short maxGrayValue;
	sourceFile >> width >> height >> maxGrayValue;
	auto pixels = LoadPixels<unsigned short>();
	return std::make_shared<PgmImage>(comments, width, height, maxGrayValue, pixels);
}

shared_ptr<PpmImage> ImageLoader::LoadPpm()
{
	comments = LoadComments();
	unsigned short maxColorValue;
	sourceFile >> width >> height >> maxColorValue;
	auto pixels = LoadPixels<RgbPixel>();
	return std::make_shared<PpmImage>(comments, width, height, maxColorValue, pixels);
}

vector<string> ImageLoader::LoadComments()
{
	vector<string> comments;
	string buffer;
	while (sourceFile.peek() == '#')
	{
		getline(sourceFile, buffer);
		comments.push_back(buffer);
	}
	return comments;
}
