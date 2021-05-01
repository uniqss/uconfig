#include "jass_luastate.h"

// Use raw function of form "int(lua_State*)"
// -- this is called a "raw C function",
// and matches the type for lua_CFunction
int LoadFileRequire(lua_State* L) {
	// use sol2 stack API to pull
	// "first argument"
	std::string path = sol::stack::get<std::string>(L, 1);

	if (path == "a") {
		std::string script = R"(
			print("Hello from module land!")
			test = 123
			return "bananas"
		)";
		// load "module", but don't run it
		luaL_loadbuffer(
			L, script.data(), script.size(), path.c_str());
		// returning 1 object left on Lua stack:
		// a function that, when called, executes the script
		// (this is what lua_loadX/luaL_loadX functions return
		return 1;
	}

	sol::stack::push(
		L, "This is not the module you're looking for!");
	return 1;
}

void jass_luastate::init(const std::string& scriptsPath)
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

	//luastate.clear_package_loaders();
	//luastate.add_package_loader(LoadFileRequire);

	const std::string package_path = luastate["package"]["path"];
	luastate["package"]["path"] = package_path + (!package_path.empty() ? ";" : "") + "./?.lua;" + scriptsPath +"?.lua";
}
