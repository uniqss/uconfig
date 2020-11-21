#include "DT_Hero_Config.h"
#include "csvhelper.h"
#include <unordered_set>

DT_Hero_Config_Data __g_DT_Hero_Config_Data;

const DT_Hero_Config_Data& GetDT_Hero_Config()
{
	return __g_DT_Hero_Config_Data;
}

// 加载函数
void DT_Hero_Config_LoadData(const std::string& pszDataFilePath)
{
	std::vector<std::string> names;
	std::vector<std::string> types;
	std::vector<std::vector<std::string>> result;
	if (!read_csv3(pszDataFilePath, names, types, result))
	{
		std::cout << "DT_Hero_Config_LoadData failed." << std::endl;
		return;
	}

	std::unordered_set<std::string> setNames;
	setNames.insert("id");
	setNames.insert("type");
	setNames.insert("name");
	setNames.insert("desc");
	std::vector<std::string> vecTypes;
	vecTypes.push_back("uint32");
	vecTypes.push_back("uint32");
	vecTypes.push_back("string");
	vecTypes.push_back("string");

	// primary key必须有
	// primary key必须唯一
	// 这里不管，可以加字段， 可以删字段，可以改字段，但是主KEY不能动结构，只能动数据。

	__g_DT_Hero_Config_Data.Datas.resize(result.size());
	for (std::size_t idx = 0; idx < result.size(); idx++)
	{
		DT_Hero_Config& rCfg = __g_DT_Hero_Config_Data.Datas[idx];

		const auto& row = result[idx];

		for (std::size_t colIdx = 0; colIdx < row.size() && colIdx < names.size(); colIdx++)
		{
			const auto& name = names[colIdx];
			const auto& type = types[colIdx];
			if (setNames.find(name) == setNames.end())
			{
				continue;
			}
			if (type != vecTypes[colIdx])
			{
				continue;
			}
			const auto& col = row[colIdx];
			DT_Hero_Config_SetColumn(rCfg, name, col);
		}

		__g_DT_Hero_Config_Data.MapItems1[rCfg.id] = &rCfg;
		__g_DT_Hero_Config_Data.MapItems2[{rCfg.type, rCfg.name}] = &rCfg;
	}
}

void DT_Hero_Config_SetColumn(DT_Hero_Config& rCfg, const std::string& name, const std::string& col)
{
	if (name == "id")
	{
		rCfg.id = std::atoi(col.c_str());
	}

	if (name == "type")
	{
		rCfg.type = std::atoi(col.c_str());
	}

	if (name == "name")
	{
		rCfg.name = col;
	}

	if (name == "desc")
	{
		rCfg.desc = col;
	}
}
