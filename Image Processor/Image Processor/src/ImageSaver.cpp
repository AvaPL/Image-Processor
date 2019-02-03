#include "../inc/ImageSaver.h"

ImageSaver::ImageSaver()
{
	targetFile.exceptions(std::ios::failbit | std::ios::badbit);
}

void ImageSaver::Save(shared_ptr<Image> imageToSave, const string& targetFilename)
{
	this->imageToSave = imageToSave;
	targetFile.open(targetFilename);
	SaveByFormat();
	targetFile.close();
}

void ImageSaver::SaveByFormat()
{
	const Format targetFormat = imageToSave->GetHeader().format;
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
	const ImageHeader header = imageToSave->GetHeader();
	targetFile << "P1\n";
	SaveComments();
	targetFile << header.width << ' ' << header.height << "\n";
	SavePixels<PbmImage>();
}

void ImageSaver::SavePgm()
{
	const ImageHeader header = imageToSave->GetHeader();
	targetFile << "P2\n";
	SaveComments();
	targetFile << header.width << ' ' << header.height << "\n" << header.maxValue << "\n";
	SavePixels<PgmImage>();
}

void ImageSaver::SavePpm()
{
	const ImageHeader header = imageToSave->GetHeader();
	targetFile << "P3\n";
	SaveComments();
	targetFile << header.width << ' ' << header.height << "\n" << header.maxValue << "\n";
	SavePixels<PpmImage>();
}

void ImageSaver::SaveComments()
{
	auto comments = imageToSave->GetHeader().comments;
	for (const auto& element : comments)
	{
		targetFile << element << '\n';
	}
}
