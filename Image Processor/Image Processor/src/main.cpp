#include <string>
#include "../inc/PbmImage.h"

int main(int argc, char* argv[])
{
	using std::string;

	PbmImage image;

	const string sourceFilename = "../Example Images/kubus.pbm";
	image.Load(sourceFilename);

	const string targetFilename = "../Example Images/test.pbm";
	image.Save(targetFilename);
}
