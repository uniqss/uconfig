#include "jass_luastate.h"

void jass_luastate::init()
{
	luastate.open_libraries(
		sol::lib::base
		, sol::lib::package
		, sol::lib::os
		, sol::lib::string
		, sol::lib::math
		, sol::lib::io
	);

	// https://github.com/ThePhD/sol2/issues/90
	/*
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::package);
	const std::string package_path = lua["package"]["path"];
	lua["package"]["path"]
		= package_path + (!package_path.empty() ? ";" : "") + test::scripts_path("proc/valid/") + "?.lua";
		*/
	const std::string package_path = luastate["package"]["path"];
	luastate["package"]["path"] = package_path + (!package_path.empty() ? ";" : "") + "./?.lua" + ";../scripts/?.lua";
}
