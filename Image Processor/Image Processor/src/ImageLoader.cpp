#include "../inc/ImageLoader.h"

using std::shared_ptr;
using std::make_shared;

ImageLoader::ImageLoader()
{
	sourceFile.exceptions(std::ios::failbit | std::ios::badbit);
}

shared_ptr<Image> ImageLoader::Load(const string& sourceFilename)
{
	sourceFile.open(sourceFilename);
	shared_ptr<Image> image = LoadByFormat();
	sourceFile.close();
	return image;
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
	ImageHeader header;
	header.comments = LoadComments();
	sourceFile >> header.width >> header.height;
	auto pixels = LoadPixels<BitPixel>(header);
	return make_shared<PbmImage>(header, pixels);
}

shared_ptr<PgmImage> ImageLoader::LoadPgm()
{
	ImageHeader header;
	header.comments = LoadComments();
	sourceFile >> header.width >> header.height >> header.maxValue;
	auto pixels = LoadPixels<GrayPixel>(header);
	return make_shared<PgmImage>(header, pixels);
}

shared_ptr<PpmImage> ImageLoader::LoadPpm()
{
	ImageHeader header;
	header.comments = LoadComments();
	sourceFile >> header.width >> header.height >> header.maxValue;
	auto pixels = LoadPixels<RgbPixel>(header);
	return make_shared<PpmImage>(header, pixels);
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
