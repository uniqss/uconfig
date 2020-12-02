#include "inja.hpp"

using json = nlohmann::json;

#include <iostream>
using namespace std;

void help(const char* programName)
{
	cout << "usage:" << programName << "templateFileName jsonDataFileName fileNameOut" << endl;
	cout << "example:" << programName << "./test/header.h.tmpl ./test/data.json ./test/header.h" << endl;
	cout << "this means using ./test/header.h.tmpl as template, using ./test/data.json as data and generate ./test/header.h" << endl;
}

int main(int argc, const char** argv)
{
	const std::string dir{ "./test/" };

	if (argc < 4)
	{
		help(argv[0]);
		return -1;
	}

	const std::string fileName = argv[1];
	const std::string fileNameData = argv[2];
	const std::string fileNameOut = argv[3];

	inja::Environment env;

	env.write_with_json_file(fileName, fileNameData, fileNameOut);

	return 0;
}
