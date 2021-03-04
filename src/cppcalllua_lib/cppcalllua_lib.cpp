#include "cppcalllua_lib.h"

#include "LuaStackAutoProtector.h"

#include "lua.hpp"

void luaPushTableString(lua_State* L, const std::vector<std::string>& vecData) {
	lua_newtable(L);
	for (auto i = 0;i < vecData.size();++i)
	{
		lua_pushinteger(L, i + 1);
		//lua_pushnumber(L, *begin);
		lua_pushstring(L, vecData[i].c_str());
		lua_settable(L, -3);
	}
}

int luaProcessOneShet(lua_State* L,
	const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::string>& vecNames,
	const std::vector<std::string>& vecTypes,
	const std::vector<std::string>& vecDescriptions)
{
	LuaStackAutoProtector o(L);
	lua_getglobal(L, "ProcessOneSheet");

	lua_pushstring(L, xlsxName.c_str());
	lua_pushstring(L, sheetName.c_str());

	luaPushTableString(L, vecNames);
	luaPushTableString(L, vecTypes);
	luaPushTableString(L, vecDescriptions);

	lua_call(L, 5, 1);

	int result = (int)lua_tointeger(L, -1);

	lua_pop(L, 1);

	return result;
}

int ProcessOneSheet(const std::string& xlsxName, const std::string& sheetName, const std::vector<std::string>& vecNames, const std::vector<std::string>& vecTypes, const std::vector<std::string>& vecDescriptions)
{
	lua_State* L;

	L = luaL_newstate();

	luaL_openlibs(L);

	luaL_dofile(L, "uniqs.lua");

	int ret = luaProcessOneShet(L, xlsxName, sheetName, vecNames, vecTypes, vecDescriptions);

	lua_close(L);

	return ret;
}

