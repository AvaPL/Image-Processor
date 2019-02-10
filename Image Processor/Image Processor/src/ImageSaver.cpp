#include "../inc/ImageSaver.h"
#include "../inc/WritingError.h"

ImageSaver::ImageSaver()
{
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
}

void ImageSaver::Save(shared_ptr<Image> imageToSave, const string& targetFilename)
{
	try
	{
		SafeSave(imageToSave, targetFilename);
	}
	catch (std::exception&)
	{
		throw WritingError("Error writing image to output.");
	}
}

void ImageSaver::SafeSave(shared_ptr<Image> imageToSave, const string& targetFilename)
{
	this->imageToSave = imageToSave;
	targetFile.open(targetFilename);
	SaveByFormat();
	targetFile.close();
}

void ImageSaver::SaveByFormat()
{
	const Format targetFormat = imageToSave->GetFormat();
	switch (targetFormat)
	{
	case PBM:
		SavePbm();
		break;
	case PGM:
		SavePgm();
		break;
	case PPM:
		SavePpm();
		break;
	default:
		targetFile.setstate(std::ios::badbit);
		break;
	}
}

void ImageSaver::SavePbm()
{
	targetFile << "P1\n";
	SaveComments();
	targetFile << imageToSave->GetWidth() << ' ' << imageToSave->GetHeight() << "\n";
	SavePixels<PbmImage>();
}

void ImageSaver::SavePgm()
{
	targetFile << "P2\n";
	SaveComments();
	targetFile << imageToSave->GetWidth() << ' ' << imageToSave->GetHeight() << "\n" << imageToSave->GetMaxValue() <<
		"\n";
	SavePixels<PgmImage>();
}

void ImageSaver::SavePpm()
{
	targetFile << "P3\n";
	SaveComments();
	targetFile << imageToSave->GetWidth() << ' ' << imageToSave->GetHeight() << "\n" << imageToSave->GetMaxValue() <<
		"\n";
	SavePixels<PpmImage>();
}

void ImageSaver::SaveComments()
{
	auto comments = imageToSave->GetComments();
	for (const auto& element : comments)
	{
		targetFile << element << '\n';
	}
}

bool ImageSaver::FileExists(const string& filename)
{
	const std::ifstream file(filename);
	return static_cast<bool>(file);
}
