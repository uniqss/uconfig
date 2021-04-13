#pragma once

#include "pch.h"

class jass_luastate
{
public:
	void init();
public:
	sol::state luastate;
};

