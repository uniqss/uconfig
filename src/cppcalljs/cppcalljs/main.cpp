#include "v8_inc.h"

#include "v8pp.h"

#include "common_functions.h"

#include "main_processonesheet.h"

#include "file_readwrite.h"
#include "module_os.h"

int main(int argc, const char** argv)
{
	v8::V8::InitializeExternalStartupData(argv[0]);
	std::unique_ptr<v8::Platform> platform(v8::platform::NewDefaultPlatform());
	v8::V8::InitializePlatform(platform.get());
	v8::V8::Initialize();

	v8pp::context context;

	init_filereadwrite(context);
	init_module_os(context);

	main_processonesheet(argc, argv, context);

	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();

	return 0;
}
