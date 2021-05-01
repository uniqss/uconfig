#include "cppcalllua_lib.h"
#include "uniqs_xlsx_reader.h"

#include "pugixml.hpp"

#include <filesystem>

void help()
{
	printf("./uniqs.xml must exist.\n");
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
	std::string scriptsPath = root.child("scriptsPath").text().as_string("./");
	if (scriptsPath == "")
	{
		scriptsPath = "./";
	}
	if (scriptsPath[scriptsPath.size() - 1] != '/')
	{
		scriptsPath = scriptsPath + '/';
	}

	std::vector<std::string> functions;
	for (auto child : root.child("functions").children("function"))
	{
		auto function = child.text().as_string();

		//printf("xxxxx %s\n", child.text().as_string());

		functions.push_back(function);
	}


	const std::filesystem::path path{ xlsxDirectory.empty() ? std::filesystem::current_path() : xlsxDirectory };

	BeforeProcess(scriptsPath);

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

		printf("%s\n", pathString.c_str());

		std::vector<std::pair<std::string, std::vector<std::vector<std::string> > > > vecxlsx;
		read_xlsx(pathString, vecxlsx, maxRowCount, maxColCount);
		int ret = 0;
		for (const auto& it : vecxlsx)
		{
			for (const std::string& function : functions)
			{
				ret = ProcessOneSheetAllDataSol2(function, pathString, it.first, it.second);
				if (ret != 0)
				{
					printf("ProcessOneSheetAllDataSol2 not ok function:%s pathString:%s. ret:%d\n", function.c_str(), pathString.c_str(), ret);
					return ret;
				}
			}
		}
	}

	AfterProcess();

	return 0;
}
