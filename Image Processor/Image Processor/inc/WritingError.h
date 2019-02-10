#pragma once
#include "ImageProcessorException.h"

class WritingError : public ImageProcessorException
{
public:
	explicit WritingError(const string& message) : ImageProcessorException(message)
	{
	}
};
