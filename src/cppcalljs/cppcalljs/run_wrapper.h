#pragma once
#include <iosfwd>
#include <array>
#include <string>
#include <sstream>
#include <stdexcept>

#include "v8pp/context.hpp"
#include "v8pp/convert.hpp"
#include "v8pp/utility.hpp"

template<typename T>
T run_script(v8pp::context& context, std::string const& source)
{
	v8::Isolate* isolate = context.isolate();

	v8::HandleScope scope(isolate);
	v8::TryCatch try_catch(isolate);
	v8::Local<v8::Value> result = context.run_script(source);
	if (try_catch.HasCaught())
	{
		std::string const msg = v8pp::from_v8<std::string>(isolate,
			try_catch.Exception()->ToString(isolate->GetCurrentContext()).ToLocalChecked());
		throw std::runtime_error(msg);
	}
	return v8pp::from_v8<T>(isolate, result);
}

static void run_script(v8pp::context& context, const std::string& source)
{
	v8::Isolate* isolate = context.isolate();

	v8::HandleScope scope(isolate);
	v8::TryCatch try_catch(isolate);
	v8::Local<v8::Value> result = context.run_script(source);
	if (try_catch.HasCaught())
	{
		std::string const msg = v8pp::from_v8<std::string>(isolate,
			try_catch.Exception()->ToString(isolate->GetCurrentContext()).ToLocalChecked());
		throw std::runtime_error(msg);
	}
}

template<typename T>
T run_file(v8pp::context& context, std::string const& fileName)
{
	v8::Isolate* isolate = context.isolate();

	v8::HandleScope scope(isolate);
	v8::TryCatch try_catch(isolate);
	v8::Local<v8::Value> result = context.run_file(fileName);
	if (try_catch.HasCaught())
	{
		std::string const msg = v8pp::from_v8<std::string>(isolate,
			try_catch.Exception()->ToString(isolate->GetCurrentContext()).ToLocalChecked());
		throw std::runtime_error(msg);
	}
	return v8pp::from_v8<T>(isolate, result);
}

static void run_file(v8pp::context& context, const std::string& fileName)
{
	v8::Isolate* isolate = context.isolate();

	v8::HandleScope scope(isolate);
	v8::TryCatch try_catch(isolate);
	v8::Local<v8::Value> result = context.run_file(fileName);
	if (try_catch.HasCaught())
	{
		std::string const msg = v8pp::from_v8<std::string>(isolate,
			try_catch.Exception()->ToString(isolate->GetCurrentContext()).ToLocalChecked());
		throw std::runtime_error(msg);
	}
}
