#include <string>
#include "../inc/ImageLoader.h"
#include "../inc/ImageSaver.h"

int main(int argc, char* argv[])
{
	using std::string;

	string sourceFilename = "../Example Images/kubus.ppm";
	string targetFilename;

	ImageLoader loader;
	auto image = loader.Load(sourceFilename);

	image = image->HistogramStretching();

	ImageSaver saver;
	auto image1 = image->ToPbm();
	targetFilename = "../Example Images/test.pbm";
	saver.Save(image1, targetFilename);
	auto image2 = image->ToPgm();
	targetFilename = "../Example Images/test.pgm";
	saver.Save(image2, targetFilename);
	auto image3 = image->ToPpm();
	targetFilename = "../Example Images/test.ppm";
	saver.Save(image3, targetFilename);
}
