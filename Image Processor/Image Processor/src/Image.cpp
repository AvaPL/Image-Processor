#include "../inc/Image.h"

void Image::LoadComments(std::ifstream& sourceFile)
{
	string buffer;
	while (sourceFile.peek() == '#')
	{
		getline(sourceFile, buffer);
		comments.push_back(buffer);
	}
}

void Image::SaveComments(std::ofstream& targetFile)
{
	for (const auto& element : comments)
	{
		targetFile << element << '\n';
	}
}
