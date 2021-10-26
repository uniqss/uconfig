#pragma once

#include "pch.h"

class jass_luastate
{
public:
	void init(const std::string& scriptsPath);
public:
	sol::state luastate;
};

