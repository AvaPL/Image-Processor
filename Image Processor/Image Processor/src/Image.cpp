#include <utility>
#include "../inc/Image.h"

void Image::SaveComments(std::ofstream& targetFile)
{
	for (const auto& element : header.comments)
	{
		targetFile << element << '\n';
	}
}
