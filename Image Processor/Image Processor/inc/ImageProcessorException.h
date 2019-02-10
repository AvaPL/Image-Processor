#pragma once
#include <exception>
#include <string>

using std::string;

class ImageProcessorException : public std::exception
{
public:
	explicit ImageProcessorException(const string& message) : exception(message.c_str())
	{
	}
};
