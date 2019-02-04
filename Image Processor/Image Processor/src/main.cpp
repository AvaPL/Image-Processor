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

	auto pbmImage = image->ToPbm();
	targetFilename = "../Example Images/test.pbm";
	saver.Save(pbmImage, targetFilename);
	auto pgmImage = image->ToPgm();
	targetFilename = "../Example Images/test.pgm";
	saver.Save(pgmImage, targetFilename);
}
