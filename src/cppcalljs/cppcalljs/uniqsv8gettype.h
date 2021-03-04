#pragma once
#include "v8_inc.h"


enum UniqsV8Types {
	UniqsV8Types_Undefined,
	UniqsV8Types_Null,
	UniqsV8Types_True,
	UniqsV8Types_False,
	UniqsV8Types_Name,
	UniqsV8Types_String,
	UniqsV8Types_Symbol,
	UniqsV8Types_Function,
	UniqsV8Types_Object,
	UniqsV8Types_Boolean,
	UniqsV8Types_Number,
	UniqsV8Types_External,
	UniqsV8Types_Int32,
	UniqsV8Types_Uint32,
	UniqsV8Types_Date,
	UniqsV8Types_ArgumentsObject,
	UniqsV8Types_BooleanObject,
	UniqsV8Types_NumberObject,
	UniqsV8Types_StringObject,
	UniqsV8Types_SymbolObject,
	UniqsV8Types_NativeError,
	UniqsV8Types_RegExp,
	UniqsV8Types_GeneratorFunction,
	UniqsV8Types_GeneratorObject,
	UniqsV8Types_Promise,
	UniqsV8Types_Map,
	UniqsV8Types_Set,
	UniqsV8Types_MapIterator,
	UniqsV8Types_SetIterator,
	UniqsV8Types_WeakMap,
	UniqsV8Types_WeakSet,
	UniqsV8Types_ArrayBuffer,
	UniqsV8Types_ArrayBufferView,
	UniqsV8Types_TypedArray,
	UniqsV8Types_Uint8Array,
	UniqsV8Types_Uint8ClampedArray,
	UniqsV8Types_Int8Array,
	UniqsV8Types_Uint16Array,
	UniqsV8Types_Int16Array,
	UniqsV8Types_Uint32Array,
	UniqsV8Types_Int32Array,
	UniqsV8Types_Float32Array,
	UniqsV8Types_Float64Array,
	UniqsV8Types_DataView,
	UniqsV8Types_SharedArrayBuffer,
	UniqsV8Types_Array,
};

static const std::pair<UniqsV8Types, char const*> UniqsV8TypesPair[] =
{
		{ UniqsV8Types_Undefined, "UniqsV8Types_Undefined" },
		{ UniqsV8Types_Null, "UniqsV8Types_Null" },
		{ UniqsV8Types_True, "UniqsV8Types_True" },
		{ UniqsV8Types_False, "UniqsV8Types_False" },
		{ UniqsV8Types_Name, "UniqsV8Types_Name" },
		{ UniqsV8Types_String, "UniqsV8Types_String" },
		{ UniqsV8Types_Symbol, "UniqsV8Types_Symbol" },
		{ UniqsV8Types_Function, "UniqsV8Types_Function" },
		{ UniqsV8Types_Object, "UniqsV8Types_Object" },
		{ UniqsV8Types_Boolean, "UniqsV8Types_Boolean" },
		{ UniqsV8Types_Number, "UniqsV8Types_Number" },
		{ UniqsV8Types_External, "UniqsV8Types_External" },
		{ UniqsV8Types_Int32, "UniqsV8Types_Int32" },
		{ UniqsV8Types_Uint32, "UniqsV8Types_Uint32" },
		{ UniqsV8Types_Date, "UniqsV8Types_Date" },
		{ UniqsV8Types_ArgumentsObject, "UniqsV8Types_ArgumentsObject" },
		{ UniqsV8Types_BooleanObject, "UniqsV8Types_BooleanObject" },
		{ UniqsV8Types_NumberObject, "UniqsV8Types_NumberObject" },
		{ UniqsV8Types_StringObject, "UniqsV8Types_StringObject" },
		{ UniqsV8Types_SymbolObject, "UniqsV8Types_SymbolObject" },
		{ UniqsV8Types_NativeError, "UniqsV8Types_NativeError" },
		{ UniqsV8Types_RegExp, "UniqsV8Types_RegExp" },
		{ UniqsV8Types_GeneratorFunction, "UniqsV8Types_GeneratorFunction" },
		{ UniqsV8Types_GeneratorObject, "UniqsV8Types_GeneratorObject" },
		{ UniqsV8Types_Promise, "UniqsV8Types_Promise" },
		{ UniqsV8Types_Map, "UniqsV8Types_Map" },
		{ UniqsV8Types_Set, "UniqsV8Types_Set" },
		{ UniqsV8Types_MapIterator, "UniqsV8Types_MapIterator" },
		{ UniqsV8Types_SetIterator, "UniqsV8Types_SetIterator" },
		{ UniqsV8Types_WeakMap, "UniqsV8Types_WeakMap" },
		{ UniqsV8Types_WeakSet, "UniqsV8Types_WeakSet" },
		{ UniqsV8Types_ArrayBuffer, "UniqsV8Types_ArrayBuffer" },
		{ UniqsV8Types_ArrayBufferView, "UniqsV8Types_ArrayBufferView" },
		{ UniqsV8Types_TypedArray, "UniqsV8Types_TypedArray" },
		{ UniqsV8Types_Uint8Array, "UniqsV8Types_Uint8Array" },
		{ UniqsV8Types_Uint8ClampedArray, "UniqsV8Types_Uint8ClampedArray" },
		{ UniqsV8Types_Int8Array, "UniqsV8Types_Int8Array" },
		{ UniqsV8Types_Uint16Array, "UniqsV8Types_Uint16Array" },
		{ UniqsV8Types_Int16Array, "UniqsV8Types_Int16Array" },
		{ UniqsV8Types_Uint32Array, "UniqsV8Types_Uint32Array" },
		{ UniqsV8Types_Int32Array, "UniqsV8Types_Int32Array" },
		{ UniqsV8Types_Float32Array, "UniqsV8Types_Float32Array" },
		{ UniqsV8Types_Float64Array, "UniqsV8Types_Float64Array" },
		{ UniqsV8Types_DataView, "UniqsV8Types_DataView" },
		{ UniqsV8Types_SharedArrayBuffer, "UniqsV8Types_SharedArrayBuffer" },
		{ UniqsV8Types_Array, "UniqsV8Types_Array" },
};

static const char* UniqsV8GetType(const v8::Local<v8::Value>& v8value)
{
	if (v8value->IsUndefined()) return UniqsV8TypesPair[UniqsV8Types_Undefined].second;
	if (v8value->IsNull()) return UniqsV8TypesPair[UniqsV8Types_Null].second;
	if (v8value->IsTrue()) return UniqsV8TypesPair[UniqsV8Types_True].second;
	if (v8value->IsFalse()) return UniqsV8TypesPair[UniqsV8Types_False].second;
	if (v8value->IsName()) return UniqsV8TypesPair[UniqsV8Types_Name].second;
	if (v8value->IsString()) return UniqsV8TypesPair[UniqsV8Types_String].second;
	if (v8value->IsSymbol()) return UniqsV8TypesPair[UniqsV8Types_Symbol].second;
	if (v8value->IsFunction()) return UniqsV8TypesPair[UniqsV8Types_Function].second;
	if (v8value->IsObject()) return UniqsV8TypesPair[UniqsV8Types_Object].second;
	if (v8value->IsBoolean()) return UniqsV8TypesPair[UniqsV8Types_Boolean].second;
	if (v8value->IsNumber()) return UniqsV8TypesPair[UniqsV8Types_Number].second;
	if (v8value->IsExternal()) return UniqsV8TypesPair[UniqsV8Types_External].second;
	if (v8value->IsInt32()) return UniqsV8TypesPair[UniqsV8Types_Int32].second;
	if (v8value->IsUint32()) return UniqsV8TypesPair[UniqsV8Types_Uint32].second;
	if (v8value->IsDate()) return UniqsV8TypesPair[UniqsV8Types_Date].second;
	if (v8value->IsArgumentsObject()) return UniqsV8TypesPair[UniqsV8Types_ArgumentsObject].second;
	if (v8value->IsBooleanObject()) return UniqsV8TypesPair[UniqsV8Types_BooleanObject].second;
	if (v8value->IsNumberObject()) return UniqsV8TypesPair[UniqsV8Types_NumberObject].second;
	if (v8value->IsStringObject()) return UniqsV8TypesPair[UniqsV8Types_StringObject].second;
	if (v8value->IsSymbolObject()) return UniqsV8TypesPair[UniqsV8Types_SymbolObject].second;
	if (v8value->IsNativeError()) return UniqsV8TypesPair[UniqsV8Types_NativeError].second;
	if (v8value->IsRegExp()) return UniqsV8TypesPair[UniqsV8Types_RegExp].second;
	if (v8value->IsGeneratorFunction()) return UniqsV8TypesPair[UniqsV8Types_GeneratorFunction].second;
	if (v8value->IsGeneratorObject()) return UniqsV8TypesPair[UniqsV8Types_GeneratorObject].second;
	if (v8value->IsPromise()) return UniqsV8TypesPair[UniqsV8Types_Promise].second;
	if (v8value->IsMap()) return UniqsV8TypesPair[UniqsV8Types_Map].second;
	if (v8value->IsSet()) return UniqsV8TypesPair[UniqsV8Types_Set].second;
	if (v8value->IsMapIterator()) return UniqsV8TypesPair[UniqsV8Types_MapIterator].second;
	if (v8value->IsSetIterator()) return UniqsV8TypesPair[UniqsV8Types_SetIterator].second;
	if (v8value->IsWeakMap()) return UniqsV8TypesPair[UniqsV8Types_WeakMap].second;
	if (v8value->IsWeakSet()) return UniqsV8TypesPair[UniqsV8Types_WeakSet].second;
	if (v8value->IsArrayBuffer()) return UniqsV8TypesPair[UniqsV8Types_ArrayBuffer].second;
	if (v8value->IsArrayBufferView()) return UniqsV8TypesPair[UniqsV8Types_ArrayBufferView].second;
	if (v8value->IsTypedArray()) return UniqsV8TypesPair[UniqsV8Types_TypedArray].second;
	if (v8value->IsUint8Array()) return UniqsV8TypesPair[UniqsV8Types_Uint8Array].second;
	if (v8value->IsUint8ClampedArray()) return UniqsV8TypesPair[UniqsV8Types_Uint8ClampedArray].second;
	if (v8value->IsInt8Array()) return UniqsV8TypesPair[UniqsV8Types_Int8Array].second;
	if (v8value->IsUint16Array()) return UniqsV8TypesPair[UniqsV8Types_Uint16Array].second;
	if (v8value->IsInt16Array()) return UniqsV8TypesPair[UniqsV8Types_Int16Array].second;
	if (v8value->IsUint32Array()) return UniqsV8TypesPair[UniqsV8Types_Uint32Array].second;
	if (v8value->IsInt32Array()) return UniqsV8TypesPair[UniqsV8Types_Int32Array].second;
	if (v8value->IsFloat32Array()) return UniqsV8TypesPair[UniqsV8Types_Float32Array].second;
	if (v8value->IsFloat64Array()) return UniqsV8TypesPair[UniqsV8Types_Float64Array].second;
	if (v8value->IsDataView()) return UniqsV8TypesPair[UniqsV8Types_DataView].second;
	if (v8value->IsSharedArrayBuffer()) return UniqsV8TypesPair[UniqsV8Types_SharedArrayBuffer].second;
	if (v8value->IsArray()) return UniqsV8TypesPair[UniqsV8Types_Array].second;
	return(0);
}
