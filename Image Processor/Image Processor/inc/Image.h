#pragma once
#include <string>
#include <fstream>
#include <utility>
#include "ImageHeader.h"

class Image
{
protected:
	ImageHeader header;

	virtual void SaveHeader(std::ofstream& targetFile) = 0;
	virtual void SaveComments(std::ofstream& targetFile);
	virtual void SavePixels(std::ofstream& targetFile) = 0;

public:
	explicit Image(ImageHeader header) : header(std::move(header))
	{
	}

	virtual ~Image() = default;

	virtual void Save(const std::string& targetFilename) = 0;
};
