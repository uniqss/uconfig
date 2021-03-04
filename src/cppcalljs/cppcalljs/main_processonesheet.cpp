#include "main_processonesheet.h"
#include <vector>
#include <string>

#include "uniqs_xlsx_reader.h"

#include "ProcessOneSheet.h"

int main_processonesheet(int argc, const char** argv, v8pp::context& context)
{
	std::vector<std::pair<std::string, std::vector<std::vector<std::string> > > > vecxlsx;

	if (argc < 2)
	{
		printf("usage: %s xlsxFileName [maxRowCount [maxColCount]] \n", argv[0]);
		return -1;
	}

	int maxRows = -1;
	if (argc > 2)
	{
		maxRows = std::atoi(argv[2]);
	}
	int maxCols = -1;
	if (argc > 3)
	{
		maxCols = std::atoi(argv[3]);
	}

	read_xlsx(argv[1], vecxlsx, maxRows, maxCols);

	int ret = 0;
	for (const auto& it : vecxlsx)
	{
		if (it.second.size() > 5)
		{
			ret = ProcessOneSheet(context, argv[1], it.first, it.second[1], it.second[2], it.second[4]);
		}
	}

#if 0
	std::string xlsxName = "testXlsxName";
	std::string sheetName = "testSheetName";

	std::vector<std::string> vecNames = { "aaaaa", "bbbbb", "cccc", "ddddd", "1111", "2222" };
	std::vector<std::string> vecTypes = { "string", "string", "string", "string", "int", "int" };
	std::vector<std::string> vecDescriptions = { "hello", "world", "", "ddddddddd", "ddd111", "ddd2222" };

	int ret = ProcessOneSheet(xlsxName, sheetName, vecNames, vecTypes, vecDescriptions);

	printf("ret:%d\n", ret);
#endif

	return 0;
}
