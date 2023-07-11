#ifndef GLFW_MODULE_MAIN
#define GLFW_MODULE_MAIN 1

// Include the Emscripten library only if targetting WebAssembly
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#endif
#include <GLFW/glfw3.h>
#include <quickjs.h>
#include <cutils.h>
#include <stdio.h>
#include <stdlib.h>

#define countof(x) (sizeof(x) / sizeof((x)[0]))

#ifndef JS_SHARED_LIBRARY
#define js_init_module js_init_module_qjsc_glfw
#endif

#if defined(_WIN32) || defined(__MINGW32__)
#define VISIBLE __declspec(dllexport)
#define HIDDEN
#else
#define VISIBLE __attribute__((visibility("default")))
#define HIDDEN __attribute__((visibility("hidden")))
#endif

#ifdef _Thread_local
#define thread_local _Thread_local
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#define thread_local __thread
#elif defined(_WIN32)
#define thread_local __declspec(thread)
#else
#error No TLS implementation found.
#endif

#define JS_CGETSET_ENUMERABLE_DEF(prop_name, fgetter, fsetter) \
  { \
    .name = prop_name, .prop_flags = JS_PROP_ENUMERABLE | JS_PROP_CONFIGURABLE, .def_type = JS_DEF_CGETSET, .u = {.getset = {.get = {.getter = fgetter}, .set = {.setter = fsetter}} } \
  }

#define JS_CGETSET_ENUMERABLE_MAGIC_DEF(prop_name, fgetter, fsetter, magic_num) \
  { \
    .name = prop_name, .prop_flags = JS_PROP_ENUMERABLE | JS_PROP_CONFIGURABLE, .def_type = JS_DEF_CGETSET_MAGIC, .magic = magic_num, .u = { \
      .getset = {.get = {.getter_magic = fgetter}, .set = {.setter_magic = fsetter}} \
    } \
  }

static inline JSAtom
js_iterator_atom(JSContext* ctx) {

  JSValue global_obj = JS_GetGlobalObject(ctx);
  JSValue symbol_constructor = JS_GetPropertyStr(ctx, global_obj, "Symbol");
  JSValue symbol_iterator = JS_GetPropertyStr(ctx, symbol_constructor, "iterator");
  JSAtom atom = JS_ValueToAtom(ctx, symbol_iterator);

  JS_FreeValue(ctx, global_obj);
  JS_FreeValue(ctx, symbol_constructor);
  JS_FreeValue(ctx, symbol_iterator);
  return atom;
}

static inline JSValue
js_newptr(JSContext* ctx, void* ptr) {
  char buf[128];
  snprintf(buf, sizeof(buf), "%p", ptr);
  return JS_NewString(ctx, buf);
}

#define GLFW_THROW() glfw_throw(ctx, __func__)

VISIBLE JSModuleDef* js_init_module(JSContext* ctx, const char* module_name);
extern thread_local BOOL glfw_initialized;
BOOL glfw_initialize(JSContext*);
JSValue glfw_throw(JSContext*, const char*);

#endif
