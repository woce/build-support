// Copyright 2011 Palm Inc.  All rights reserved.

#ifndef V8_V8_INSPECTOR_H_
#define V8_V8_INSPECTOR_H_

#include "v8.h"

#ifdef _WIN32
typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;  // NOLINT
typedef long long int64_t;  // NOLINT

// Setup for Windows DLL export/import. See v8.h in this directory for
// information on how to build/use V8 as a DLL.
#if defined(BUILDING_V8_SHARED) && defined(USING_V8_SHARED)
#error both BUILDING_V8_SHARED and USING_V8_SHARED are set - please check the\
  build configuration to ensure that at most one of these is set
#endif

#ifdef BUILDING_V8_SHARED
#define EXPORT __declspec(dllexport)
#elif USING_V8_SHARED
#define EXPORT __declspec(dllimport)
#else
#define EXPORT
#endif

#else  // _WIN32

// Setup for Linux shared library export. See v8.h in this directory for
// information on how to build/use V8 as shared library.
#if defined(__GNUC__) && (__GNUC__ >= 4) && defined(V8_SHARED)
#define EXPORT __attribute__ ((visibility("default")))
#else  // defined(__GNUC__) && (__GNUC__ >= 4)
#define EXPORT
#endif  // defined(__GNUC__) && (__GNUC__ >= 4)

#endif  // _WIN32


/**
 * Inspector support for the V8 JavaScript engine.
 */
namespace v8 {
namespace internal {

class Context;
class FunctionTemplateInfo;
class JSArray;
class JSFunction;
class JSObject;
class ObjectTemplateInfo;
class Proxy;
class SharedFunctionInfo;
class SignatureInfo;
class String;
class TemplateInfo;
class TypeSwitchInfo;
}  // internal


class EXPORT Inspector {
 public:
  static internal::TemplateInfo*
    TemplateHandleToInternalObj(Handle<Template> that);

  static internal::FunctionTemplateInfo*
    FunctionTemplateHandleToInternalObj(Handle<FunctionTemplate> that);

  static internal::ObjectTemplateInfo*
    ObjectTemplateHandleToInternalObj(Handle<ObjectTemplate> that);

  static internal::Object* DataHandleToInternalObj(Handle<Data> that);

  static internal::JSObject* ObjectHandleToInternalObj(Handle<Object> that);

  static internal::Object* IntegerHandleToInternalObj(Handle<Integer> that);

  static internal::JSArray* ArrayHandleToInternalObj(Handle<Array> that);

  static internal::String* StringHandleToInternalObj(Handle<String> that);

  static internal::SharedFunctionInfo*
      ScriptHandleToInternalObj(Handle<Script> that);

  static internal::JSFunction*
      FunctionHandleToInternalObj(Handle<Function> that);

  static internal::JSObject* MessageHandleToInternalObj(Handle<Message> that);

  static internal::Context* ContextHandleToInternalObj(Handle<Context> that);

  static internal::SignatureInfo*
    SignatureHandleToInternalObj(Handle<Signature> that);

  static internal::TypeSwitchInfo*
    TypeSwitchHandleToInternalObj(Handle<TypeSwitch> that);

  static internal::Proxy* ExternalHandleToInternalObj(Handle<External> that);

  static internal::Object* ValueHandleToInternalObj(Handle<Value> that);

  static void Print(Handle<Object> that);
};


}  // namespace v8


#undef EXPORT


#endif  // V8_V8_INSPECTOR_H_
