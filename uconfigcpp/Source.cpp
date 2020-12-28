#include "uniqs_xlsx_reader.h"

#include "process_one_sheet.h"

int main(int argc, const char** argv)
{
	std::vector<std::pair<std::string, std::vector<std::vector<std::string> > > > vecxlsx;

	if (argc < 2)
	{
		printf("usage: %s xlsxFileName \n", argv[0]);
		return -1;
	}

	read_xlsx(argv[1], vecxlsx);

	int ret = 0;
	for (const auto& it : vecxlsx)
	{
		if (it.second.size() > 5)
		{
			ret = ProcessOneSheet_lua(argv[1], it.first, it.second[1], it.second[2], it.second[4]);
		}
	}

	return 0;
}
