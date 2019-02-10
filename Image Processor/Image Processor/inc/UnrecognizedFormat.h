#pragma once
#include "ImageProcessorException.h"

class UnrecognizedFormat : public ImageProcessorException
{
public:
	explicit UnrecognizedFormat(const string& message) : ImageProcessorException(message)
	{
	}
};
