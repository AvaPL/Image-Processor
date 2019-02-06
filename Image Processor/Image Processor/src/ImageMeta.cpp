#include "../inc/ImageMeta.h"

void ImageMeta::AddComment(const string& comment)
{
	if (comment[0] == '#')
		comments.push_back(comment);
	else
		comments.push_back('#' + comment);
}
