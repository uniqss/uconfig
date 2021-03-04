#include <v8pp/module.hpp>
#include <v8pp/class.hpp>
#include <v8pp/config.hpp>
#include <v8pp/context.hpp>

#include "v8pp/json.hpp"
#include "v8pp/object.hpp"
#include "v8pp/property.hpp"

#include "run_wrapper.h"

#include <fstream>

class file_base
{
public:
	bool is_open() const { return stream_.is_open(); }
	bool good() const { return stream_.good(); }
	bool eof() const { return stream_.eof(); }
	void close() { stream_.close(); }

protected:
	std::fstream stream_;
};

class file_writer : public file_base
{
public:
	explicit file_writer(v8::FunctionCallbackInfo<v8::Value> const& args)
	{
		if (args.Length() == 1)
		{
			v8::String::Utf8Value const str(args.GetIsolate(), args[0]);
			open(*str);
		}
	}

	bool open(char const* path)
	{
		stream_.open(path, std::ios_base::out);
		return stream_.good();
	}

	void print(v8::FunctionCallbackInfo<v8::Value> const& args)
	{
		v8::HandleScope scope(args.GetIsolate());

		for (int i = 0; i < args.Length(); ++i)
		{
			if (i > 0) stream_ << ' ';
			v8::String::Utf8Value const str(args.GetIsolate(), args[i]);
			stream_ << *str;
		}
	}

	void println(v8::FunctionCallbackInfo<v8::Value> const& args)
	{
		print(args);
		stream_ << std::endl;
	}
};

class file_reader : public file_base
{
public:
	explicit file_reader(char const* path)
	{
		open(path);
	}

	bool open(const char* path)
	{
		stream_.open(path, std::ios_base::in);
		return stream_.good();
	}

	v8::Local<v8::Value> getline(v8::Isolate* isolate)
	{
		if (stream_.good() && !stream_.eof())
		{
			std::string line;
			std::getline(stream_, line);
			return v8pp::to_v8(isolate, line);
		}
		else
		{
			return v8::Undefined(isolate);
		}
	}
};

template<typename Traits, class T>
static auto create_Obj(v8::FunctionCallbackInfo<v8::Value> const& args)
{
	auto x(new T(args));
	return x;
}

void init_filereadwrite(v8pp::context& context)
{
	typedef v8pp::raw_ptr_traits Traits;

	v8::Isolate* isolate = context.isolate();
	v8::HandleScope scope(isolate);

	auto const FileWriter_ctor = [](v8::FunctionCallbackInfo<v8::Value> const& args)
	{
		printf("FileWriter_ctor lambda create_Obj\n");
		return create_Obj<Traits, file_writer>(args);
	};
	auto const FileWriter_dtor = [](v8::Isolate*, typename Traits::template object_pointer_type<file_writer> const& obj)
	{
		Traits::destroy(obj);
	};
	v8pp::class_<file_writer, Traits> FileWriter_class(isolate, FileWriter_dtor);
	FileWriter_class
		.template ctor<v8::FunctionCallbackInfo<v8::Value> const&>(FileWriter_ctor)
		.set("open", &file_writer::open)
		.set("print", &file_writer::print)
		.set("println", &file_writer::println)
		.set("close", &file_writer::close)
		;
	context.set("FileWriter", FileWriter_class);
}
