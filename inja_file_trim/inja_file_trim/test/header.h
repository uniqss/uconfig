#pragma once

#include<vector>
#include<map>
#include "uniqsconfigtypes.h"

class DT_Hero_Config
{
public:
	DT_Hero_Config()
	{
		id = 0;
		type = 0;
		name = "";
		desc = "";
	}
	// 字段类型 字段名
	uint32 id;
	uint32 type;
	string name;
	string desc;
};

class DT_Hero_Config_Data
{
public:
	std::vector< DT_Hero_Config> Datas;
	std::map<uint32, DT_Hero_Config*> MapItems1;
	std::map<std::tuple<uint32, string>, DT_Hero_Config*> MapItems2;
public:
	const DT_Hero_Config* FindByKey1(const uint32& Id) const
	{
		auto it = MapItems1.find(Id);
		if (it != MapItems1.end())
		{
			return it->second;
		}
		return nullptr;
	}
	const DT_Hero_Config* FindByKey2(const uint32& Type, const string& Name) const
	{
		auto it = MapItems2.find(make_tuple(Type, Name));
		if (it != MapItems2.end())
		{
			return it->second;
		}
		return nullptr;
	}
};
extern DT_Hero_Config_Data __g_DT_Hero_Config_Data;
const DT_Hero_Config_Data& GetDT_Hero_Config();
// 加载函数
void DT_Hero_Config_LoadData(const std::string& pszDataFilePath);
void DT_Hero_Config_SetColumn(DT_Hero_Config& rCfg, const std::string& name, const std::string& col);
