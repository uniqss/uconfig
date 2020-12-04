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
		name = 0;
		desc = 0;
		model_id = 0;
		icon = 0;
		set_paint = 0;
		quality = 0;
	}
	
	uint32 id;// 百灵id
	uint32 type;// 百灵类型
	string name;// 百灵名字
	string desc;// 百灵介绍
	uint32 model_id;// 角色模型
	string icon;// 头像icon
	string set_paint;// 图片名字
	uint32 quality;// 百灵品质
};

class DT_Hero_Config_Data
{
public:
	std::vector< DT_Hero_Config> Datas;

	std::map<uint32, DT_Hero_Config*> MapItems1;
	std::map<std::tuple<uint32, string>, DT_Hero_Config*> MapItems2;
	std::map<std::tuple<string, uint32, string>, DT_Hero_Config*> MapItems3;
public:

	const DT_Hero_Config* FindByKey1(const uint32& id) const
	{
		auto it = MapItems1.find(id);
		if (it != MapItems1.end())
		{
			return it->second;
		}
		return nullptr;
	}

	const DT_Hero_Config* FindByKey2() const
	{
		auto it = MapItems2.find(make_tuple(type, name));
		if (it != MapItems2.end())
		{
			return it->second;
		}
		return nullptr;
	}

	const DT_Hero_Config* FindByKey3() const
	{
		auto it = MapItems3.find(make_tuple(desc, model_id, icon));
		if (it != MapItems3.end())
		{
			return it->second;
		}
		return nullptr;
	}

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
