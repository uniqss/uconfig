#pragma once

#include "pch.h"

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
