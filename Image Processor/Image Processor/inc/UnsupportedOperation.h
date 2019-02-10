#pragma once
#include "ImageProcessorException.h"

class UnsupportedOperation : public ImageProcessorException
{
public:
	explicit UnsupportedOperation(const string& message) : ImageProcessorException(message)
	{
	}
};
