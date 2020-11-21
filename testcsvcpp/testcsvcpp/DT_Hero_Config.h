#pragma once

#include<stdint.h>
#include<string>
#include<vector>
#include<map>

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
	uint32_t id;
	uint32_t type;
	std::string name;
	std::string desc;
};

class DT_Hero_Config_Data
{
public:
	std::vector< DT_Hero_Config> Datas;
	std::map<uint32_t, DT_Hero_Config*> MapItems1;
	std::map<std::tuple<uint32_t, std::string>, DT_Hero_Config*> MapItems2;
public:
	const DT_Hero_Config* FindByKey1(const uint32_t& Id) const
	{
		auto it = MapItems1.find(Id);
		if (it != MapItems1.end())
		{
			return it->second;
		}
		return nullptr;
	}
	const DT_Hero_Config* FindByKey2(const uint32_t& Type, const std::string& Name) const
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
