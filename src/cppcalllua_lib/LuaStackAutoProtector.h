#pragma once

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuaStackAutoProtector
{
private:
	int m_nTop;
	lua_State* m_pLuaState;
public:
	LuaStackAutoProtector(lua_State* L)
	{
		m_pLuaState = L;
		m_nTop = lua_gettop(m_pLuaState);
	}
	~LuaStackAutoProtector()
	{
		lua_settop(m_pLuaState, m_nTop);
	}
};
