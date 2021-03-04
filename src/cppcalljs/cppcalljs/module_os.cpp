#include "module_os.h"

#include "v8pp/module.hpp"
#include "v8pp/property.hpp"
#include "v8pp/context.hpp"
#include "v8pp/convert.hpp"
#include "v8pp/utility.hpp"


//static int os_execute(lua_State* L) {
//	const char* cmd = luaL_optstring(L, 1, NULL);
//	int stat;
//	errno = 0;
//	stat = system(cmd);
//	if (cmd != NULL)
//		return luaL_execresult(L, stat);
//	else {
//		lua_pushboolean(L, stat);  /* true if there is a shell */
//		return 1;
//	}
//}
//
//
//static int os_remove(lua_State* L) {
//	const char* filename = luaL_checkstring(L, 1);
//	return luaL_fileresult(L, remove(filename) == 0, filename);
//}
//
//
//static int os_rename(lua_State* L) {
//	const char* fromname = luaL_checkstring(L, 1);
//	const char* toname = luaL_checkstring(L, 2);
//	return luaL_fileresult(L, rename(fromname, toname) == 0, NULL);
//}

static int os_execute(const char* cmd) {
	return system(cmd);
}

static int os_remove(const char* filename) {
	return remove(filename);
}

static int os_rename(const char* fromname, const char* toname) {
	return rename(fromname, toname);
}

void init_module_os(v8pp::context& context)
{
	v8::Isolate* isolate = context.isolate();
	v8::HandleScope scope(isolate);

	// module使用第一步，声明 module
	v8pp::module osModule(isolate);

	// module使用第二步，set设置常量、函数、属性(只读属性、读写属性)
	osModule.set("execute", &os_execute);
	osModule.set("remove", &os_remove);
	osModule.set("rename", &os_rename);
	// module使用第三步，设置module
	context.set("os", osModule);
}
