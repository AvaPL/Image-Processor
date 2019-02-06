#pragma once
#include <string>
#include <vector>
#include "Format.h"

using std::vector;
using std::string;

class ImageMeta
{
	Format format;
	vector<string> comments;
	unsigned short maxValue;

public:
	explicit ImageMeta(const Format format, const unsigned short maxValue = 0) : format(format), maxValue(maxValue)
	{
	}

	Format GetFormat() const { return format; }
	void AddComment(const string& comment);
	const vector<string>& GetComments() const { return comments; }
	void SetMaxValue(const unsigned short newMaxValue) { maxValue = newMaxValue; }
	unsigned short GetMaxValue() const { return maxValue; }
};
