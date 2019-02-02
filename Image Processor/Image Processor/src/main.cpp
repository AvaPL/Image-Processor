#include <string>
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"
#include "../inc/PpmImage.h"

int main(int argc, char* argv[])
{
	using std::string;

	PpmImage image;

	const string sourceFilename = "../Example Images/kubus.ppm";
	image.Load(sourceFilename);

	const string targetFilename = "../Example Images/test.ppm";
	image.Save(targetFilename);
}
