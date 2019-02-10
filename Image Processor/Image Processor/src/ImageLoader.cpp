#include "../inc/ImageLoader.h"
#include "../inc/UnrecognizedFormat.h"
#include "../inc/ReadingError.h"

using std::shared_ptr;
using std::make_shared;

ImageLoader::ImageLoader()
{
	sourceFile.exceptions(std::ios::failbit | std::ios::badbit);
}

shared_ptr<Image> ImageLoader::Load(const string& sourceFilename)
{
	try
	{
		sourceFile.open(sourceFilename);
	}
	catch (std::exception&)
	{
		throw ReadingError("Error opening image.");
	}
	shared_ptr<Image> image = LoadByFormat();
	sourceFile.close();
	return image;
}

shared_ptr<Image> ImageLoader::LoadByFormat()
{
	string buffer;
	try
	{
		getline(sourceFile, buffer);
		if (buffer == "P1")
			return LoadPbm();
		if (buffer == "P2")
			return LoadPgm();
		if (buffer == "P3")
			return LoadPpm();
	}
	catch (ReadingError&)
	{
		throw;
	}
	catch (std::exception&)
	{
		throw ReadingError("Error reading image meta from input.");
	}
	throw UnrecognizedFormat("Unrecognized image format when loading.");
}

shared_ptr<PbmImage> ImageLoader::LoadPbm()
{
	auto meta = ImageMeta(PBM);
	LoadComments(meta);
	size_t width, height;
	sourceFile >> width >> height;
	auto pixels = LoadPixelMap<BitPixel>(width, height);
	return make_shared<PbmImage>(meta, pixels);
}

shared_ptr<PgmImage> ImageLoader::LoadPgm()
{
	auto meta = ImageMeta(PGM);
	LoadComments(meta);
	size_t width, height;
	sourceFile >> width >> height;
	LoadMaxValue(meta);
	auto pixels = LoadPixelMap<GrayPixel>(width, height);
	return make_shared<PgmImage>(meta, pixels);
}

shared_ptr<PpmImage> ImageLoader::LoadPpm()
{
	auto meta = ImageMeta(PPM);
	LoadComments(meta);
	size_t width, height;
	sourceFile >> width >> height;
	LoadMaxValue(meta);
	auto pixels = LoadPixelMap<RgbPixel>(width, height);
	return make_shared<PpmImage>(meta, pixels);
}

void ImageLoader::LoadMaxValue(ImageMeta& meta)
{
	unsigned short maxValue;
	sourceFile >> maxValue;
	meta.SetMaxValue(maxValue);
}

void ImageLoader::LoadComments(ImageMeta& meta)
{
	string buffer;
	while (sourceFile.peek() == '#')
	{
		getline(sourceFile, buffer);
		meta.AddComment(buffer);
	}
}
