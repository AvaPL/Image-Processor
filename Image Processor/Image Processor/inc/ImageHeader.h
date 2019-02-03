#pragma once
#include <string>
#include <vector>

struct ImageHeader
{
	std::vector<std::string> comments;
	int width;
	int height;
	unsigned short maxValue;

	ImageHeader(): width(), height(), maxValue()
	{
	}
};
