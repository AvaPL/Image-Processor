#pragma once
#include "ImageProcessorException.h"

class ReadingError : public ImageProcessorException
{
public:
	explicit ReadingError(const string& message) : ImageProcessorException(message)
	{
	}
};
