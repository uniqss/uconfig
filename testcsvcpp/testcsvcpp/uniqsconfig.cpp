#include "uniqsconfig.h"

#include "DT_Hero_Config.h"

void UniqsLoadAllConfigDatas(const std::string& pszDataFilePath)
{
	std::string path = pszDataFilePath;
	if (!path.empty() && path[path.size() - 1] != '/')
	{
		path += "/";
	}

	DT_Hero_Config_LoadData(pszDataFilePath + "DT_Hero_Config.csv");
}
