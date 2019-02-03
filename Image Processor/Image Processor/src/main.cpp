#include <string>
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/PpmImage.h"

int main(int argc, char* argv[])
{
	using std::string;
	using std::make_unique;

	std::unique_ptr<Image> image;

	image = make_unique<PbmImage>();
	const string sourceFilename1 = "../Example Images/kubus.pbm";
	image->Load(sourceFilename1);
	const string targetFilename1 = "../Example Images/test1.pbm";
	image->Save(targetFilename1);

	image = make_unique<PgmImage>();
	const string sourceFilename2 = "../Example Images/kubus.pgm";
	image->Load(sourceFilename2);
	const string targetFilename2 = "../Example Images/test2.pgm";
	image->Save(targetFilename2);

	image = make_unique<PpmImage>();
	const string sourceFilename3 = "../Example Images/kubus.ppm";
	image->Load(sourceFilename3);
	const string targetFilename3 = "../Example Images/test3.ppm";
	image->Save(targetFilename3);
}
