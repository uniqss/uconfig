#include "cppcalllua_lib.h"
#include "uniqs_xlsx_reader.h"

#include "pugixml.hpp"

#include <filesystem>

void help()
{
	printf("./uniqs.xml must exist.");
}

int main(int argc, const char** argv)
{
	pugi::xml_document doc;
	auto result = doc.load_file("./uniqs.xml");
	if (!result)
	{
		help();
		return -1;
	}
	auto root = doc.child("root");
	if (root.empty())
	{
		help();
		return -1;
	}
	std::string xlsxDirectory = root.child("directory").text().as_string("");
	int maxRowCount = root.child("maxRowCount").text().as_int(-1);
	int maxColCount = root.child("maxColCount").text().as_int(-1);

	const std::filesystem::path path{ xlsxDirectory.empty() ? std::filesystem::current_path() : xlsxDirectory };

	BeforeProcess();

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		const auto filenameStr = entry.path().filename().string();
		if (entry.is_directory())
		{
			continue;
		}
		else if (!entry.is_regular_file())
		{
			continue;
		}

		const auto pathString = entry.path().string();

		printf(pathString.c_str());

		std::vector<std::pair<std::string, std::vector<std::vector<std::string> > > > vecxlsx;
		read_xlsx(pathString, vecxlsx, maxRowCount, maxColCount);
		int ret = 0;
		for (const auto& it : vecxlsx)
		{
			ret = ProcessOneSheetAllDataSol2(pathString, it.first, it.second);
			if (ret != 0)
			{
				printf("ProcessOneSheetAllDataSol2 not ok. ret:%d\n", ret);
				return ret;
			}
		}
	}

	AfterProcess();

	return 0;
}
