#include <string>
#include "../inc/ImageLoader.h"

int main(int argc, char* argv[])
{
	using std::string;

	string sourceFilename = "../Example Images/kubus.pbm";
	string targetFilename = "../Example Images/test.pbm";
	ImageLoader loader;
	auto image = loader.Load(sourceFilename);
	image->Save(targetFilename);

	sourceFilename = "../Example Images/kubus.pgm";
	targetFilename = "../Example Images/test.pgm";
	image = loader.Load(sourceFilename);
	image->Save(targetFilename);

	sourceFilename = "../Example Images/kubus.ppm";
	targetFilename = "../Example Images/test.ppm";
	image = loader.Load(sourceFilename);
	image->Save(targetFilename);
}
