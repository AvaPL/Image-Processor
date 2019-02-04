#include <string>
#include "../inc/ImageLoader.h"
#include "../inc/ImageSaver.h"

int main(int argc, char* argv[])
{
	using std::string;

	string sourceFilename = "../Example Images/kubus.ppm";
	string targetFilename = "../Example Images/test.ppm";
	ImageLoader loader;
	auto image = loader.Load(sourceFilename);
	ImageSaver saver;
	saver.Save(image, targetFilename);

	auto image2 = image->ToPbm();
	targetFilename = "../Example Images/test.pbm";
	saver.Save(image2, targetFilename);
	auto image3 = image->ToPgm();
	targetFilename = "../Example Images/test.pgm";
	saver.Save(image3, targetFilename);
}
