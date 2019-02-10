#include <string>
#include "../inc/ImageLoader.h"
#include "../inc/ImageSaver.h"
#include "../inc/ImageProcessorException.h"

using std::string;

int main(int argc, char* argv[])
{
	//Example program.
	string sourceFilename = "../Example Images/Lena.ppm";
	string targetFilename;
	ImageLoader loader;
	ImageSaver saver;

	try
	{
		auto image = loader.Load(sourceFilename);

		image = image->Contouring();

		auto image1 = image->ToPbm();
		targetFilename = "../Example Images/ProcessingEffect.pbm";
		saver.Save(image1, targetFilename);
		auto image2 = image->ToPgm();
		targetFilename = "../Example Images/ProcessingEffect.pgm";
		saver.Save(image2, targetFilename);
		auto image3 = image->ToPpm();
		targetFilename = "../Example Images/ProcessingEffect.ppm";
		saver.Save(image3, targetFilename);
	}
	catch (ImageProcessorException& e)
	{
		std::cout << e.what();
		system("pause");
	}
}
