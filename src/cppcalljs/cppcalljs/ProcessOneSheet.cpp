#include "ProcessOneSheet.h"

#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <v8pp/config.hpp>
#include <v8pp/context.hpp>
#include <v8pp/call_v8.hpp>

#include "v8pp/json.hpp"
#include "v8pp/object.hpp"
#include "v8pp/property.hpp"

int ProcessOneSheet(
	v8pp::context& context,
	const std::string& xlsxName,
	const std::string& sheetName,
	const std::vector<std::string>& vecNames, /* 第2行 */
	const std::vector<std::string>& vecTypes, /* 第3行 */
	const std::vector<std::string>& vecDescriptions /* 第5行 */
)
{
	v8::Isolate* isolate = context.isolate();
	v8::HandleScope scope(isolate);
	v8::Local<v8::Function> fun;

	v8::TryCatch try_catch(isolate);

	fun = context.run_file("uniqs.js").As<v8::Function>();
	v8pp::call_v8(isolate, fun, fun, xlsxName, sheetName, vecNames, vecTypes, vecDescriptions);

	if (try_catch.HasCaught())
	{
		std::string const msg = v8pp::from_v8<std::string>(isolate,
			try_catch.Exception()->ToString(isolate->GetCurrentContext()).ToLocalChecked());
		throw std::runtime_error(msg);
	}

	return 0;
}
