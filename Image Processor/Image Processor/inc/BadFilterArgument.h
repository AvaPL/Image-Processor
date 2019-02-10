#pragma once
#include "ImageProcessorException.h"

class BadFilterArgument : public ImageProcessorException
{
public:
	explicit BadFilterArgument(const string& message) : ImageProcessorException(message)
	{
	}
};
