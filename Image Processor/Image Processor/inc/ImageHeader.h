#pragma once
#include <string>
#include <vector>
#include "Format.h"

//TODO: This should be a class.

struct ImageHeader
{
	Format format;
	std::vector<std::string> comments;
	int width;
	int height;
	unsigned short maxValue;

	ImageHeader(): format(), width(), height(), maxValue()
	{
	}
};
