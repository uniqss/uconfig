
#include "Lua/LuaLibrary.h"
#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/Vector.h"

#include <vector>

#include "cppcalllua_lib.h"

#include "LuaStackAutoProtector.h"

int luaProcessOneSheetAllData(lua_State* L,
	const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::vector<std::string>>& datas)
{
	luabridge::LuaRef ProcessOneSheetAllData = luabridge::getGlobal(L, "ProcessOneSheetAllData");
	int result = ProcessOneSheetAllData(xlsxName, sheetName, datas);

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
