#include "common_functions.h"

static int log(char const* s)
{
	printf("log s:%s", s);
	return 0;
}
static int h(v8::Isolate*, int x, int y) { return x + y; }

void set_common_functions(v8pp::context& context)
{
	//v8pp::context context;
	v8::Isolate* isolate = context.isolate();
	v8::HandleScope scope(isolate);

#if 1
	// test export log function to js
	//context.set("log", v8pp::wrap_function(isolate, "log", &log));
	//check_eq("log", run_script<void>(context, "f(1)"), 1);



	context.set("h", v8pp::wrap_function(isolate, "h", &h));
	//check_eq("h", run_script<int>(context, "h(1, 2)"), 3);
#endif
}
