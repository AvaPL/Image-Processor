#include <utility>
#include "../inc/Image.h"

Image::Image(std::vector<string> comments, const int width, const int height) : width(width),
                                                                                height(height), comments(std::move(comments))
{
}

void Image::SaveComments(std::ofstream& targetFile)
{
	for (const auto& element : comments)
	{
		targetFile << element << '\n';
	}
}
