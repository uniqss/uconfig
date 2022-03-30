#include "pch.h"

#if 0
#include "Lua/LuaLibrary.h"
#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/Vector.h"
#endif

#include <vector>

#include "uconfig_lib.h"

#include "LuaStackAutoProtector.h"

#include "jass_luastate.h"

int luaProcessOneSheetAllData(lua_State* L,
	const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::vector<std::string>>& datas)
{
	int result = 0;

#if 0
	luabridge::LuaRef ProcessOneSheetAllData = luabridge::getGlobal(L, "ProcessOneSheetAllData");
	result = ProcessOneSheetAllData(xlsxName, sheetName, datas);
#endif

	return result;
}

int ProcessOneSheetAllData(const std::string& xlsxName, const std::string& sheetName,
	const std::vector < std::vector<std::string>>& datas)
{
	lua_State* L;

	L = luaL_newstate();

	luaL_openlibs(L);

	luaL_dofile(L, "uniqs.lua");

	int ret = luaProcessOneSheetAllData(L, xlsxName, sheetName, datas);

	lua_close(L);

	return ret;
}

jass_luastate luastate;

int BeforeProcess(const std::string& scriptsPath)
{
	int ret = 0;
	
	luastate.init(scriptsPath);
	sol::state_view lua = luastate.luastate;
	lua.script_file(scriptsPath + "uniqs.lua");
	

	return ret;
}

int ProcessOneSheetAllDataSol2(const std::string& function, const std::string& xlsxName, const std::string& sheetName,
	const std::vector < std::vector<std::string>>& datas)
{
	sol::state_view lua = luastate.luastate;
	sol::function func = lua[function];
	if (!func.valid())
	{
		printf("ProcessOneSheetAllDataSol2 lua function [%s] load error.\n", function.c_str());
		return -1;
	}
	int result = func(xlsxName, sheetName, datas);
	return result;
}

int AfterProcess(const std::string& function, const std::vector<std::string>& vecSheetNames)
{
	sol::state_view lua = luastate.luastate;
	sol::function func = lua[function];
	if (!func.valid())
	{
		printf("AfterProcess lua function [%s] load error.\n", function.c_str());
		return -1;
	}

	int result = func(vecSheetNames);
	return result;
}
