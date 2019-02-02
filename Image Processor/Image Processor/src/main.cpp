#include <string>
#include "../inc/PbmImage.h"
#include "../inc/PgmImage.h"

int main(int argc, char* argv[])
{
	using std::string;

	PgmImage image;

	const string sourceFilename = "../Example Images/kubus.pgm";
	image.Load(sourceFilename);

	const string targetFilename = "../Example Images/test.pgm";
	image.Save(targetFilename);
}
