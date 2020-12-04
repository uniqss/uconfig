# uniqsconfiggenerator
uniqs design config generator, xlsx files to definition and data files. 

## supported languages: C/C++/Go/Lua/Js/Java/Python/Anything......(if only template given)

## xlsx definition:
|#|	|	|	|	|	|	|	|	|
|---|---|---|---|---|---|---|---|---|
|PrimaryKey|1|2|2|3|3|3|
|英文名|id|type|name|desc|model_id|icon|set_paint|quality|
|类型|uint32|uint32|string|string|uint32|string|string|uint32|
|哪里使用|cs|cs|cs|cs|cs|cs|cs|cs|
|中文名|道具id|百灵类型|百灵名字|百灵介绍|角色模型|头像icon|图片名字|百灵品质|
|数据|1001|2001|张小三|哈小喽|zhangsan.mdl|zhangsan.ico|zhangsan.png|3|
### xlsx definition note:
* first line: '#' means comment. this column will not be processed.
* second line: Primary key. support integer(int32/uint32/int64/uint64) and string single primary key. support multi primary key. support multi group of multi primary key.
* third line: code name. this line will be generated in code.
* forth line: type. every language may need a transfer in your template.
* fifth line: used in which peer. 'c' means client, whereas 's' means server.
* sixth line: your comment. anything.
### sample template(cpp):
```
#pragma once

#include<vector>
#include<map>
#include "uniqsconfigtypes.h"

class {{SheetName}}
{
public:
	{{SheetName}}()
	{
{% for i in range(length(CodeName)) %}
		{{ at(CodeName, i) }} = 0;{% endfor %}
	}
	{% for i in range(length(CodeName)) %}
	{{ at(Type, i) }} {{ at(CodeName, i) }};// {{ at(Description, i) }}{% endfor %}
};

class {{SheetName}}_Data
{
public:
	std::vector< {{SheetName}}> Datas;
{% for key, value in PrimaryKeyTypes) %}
	{% if length(value) == 1 %}std::map<{{ at(value, 0) }}, {{SheetName}}*> MapItems{{ key }};{% else %}std::map<std::tuple<{% for idx in range(length(value) - 1) %}{{at(value, idx)}}, {% endfor %}{{last(value)}}>, {{SheetName}}*> MapItems{{ key }};{% endif %}{% endfor %}
public:
	const {{SheetName}}* FindByKey1(const uint32& Id) const
	{
		auto it = MapItems1.find(Id);
		if (it != MapItems1.end())
		{
			return it->second;
		}
		return nullptr;
	}
	const {{SheetName}}* FindByKey2(const uint32& Type, const string& Name) const
	{
		auto it = MapItems2.find(make_tuple(Type, Name));
		if (it != MapItems2.end())
		{
			return it->second;
		}
		return nullptr;
	}
};
extern {{SheetName}}_Data __g_{{SheetName}}_Data;
const {{SheetName}}_Data& Get{{SheetName}}();
// 加载函数
void {{SheetName}}_LoadData(const std::string& pszDataFilePath);
void {{SheetName}}_SetColumn({{SheetName}}& rCfg, const std::string& name, const std::string& col);

```
### the sample will be generated like this(cpp):
```
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

```

## 逻辑代码没被更新以前，有几种情况：
|语言|数据更新|新增列|删除列|列改名|
|---|---|---|---|---|
|C++|OK|跳过|默认值|跳过+默认值|
|Lua|OK|热更结构体|热更结构体|热更结构体|
|Go|OK|跳过|默认值|跳过+默认值|
|Js|OK|热更结构体|热更结构体|热更结构体|

### 数据的类型：csv/json
### 定义体为生成的代码

## 需求：
    从XLSX生成代码。支持任意语言，只需要简单修改一下生成模板，就能生成任意语言。
    使用极为简单，模板语法非常精简，或者使用非常简单的JAVASCRIPT功能
    模板实现或者是嵌入脚本实现
    模板实现：mustache或者mako或者其他不容易与现有代码冲突的替换模板
    中间用的数据源可以是JSON/CSV/XML/任何格式
## 思路
    模板
        vue：模板实在太难写，全是div
        inja：能满足大部分需求，但是语法不够精简，需要提供的需求：
            1、需要join函数，最好是 join(array, spliter, elementLeft, elementRight)，能大大简化模板
            2、需要能二次解析。{{ {{ASDF}} }} 意思是先解析{{ASDF}}，值为ASDF_VALUE, 再解析{{ASDF_VALUE}}
## 语言
        一、集成google V8，搞一套用JSON生成的思路(不太好)
        二、集成Python,搞一套Python生成的思路(不太好)
        二、自己实现一套flex and bison
