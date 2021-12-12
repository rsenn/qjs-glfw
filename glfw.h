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

JSValue glfw_throw(JSContext* ctx);

#ifndef JS_SHARED_LIBRARY
#define js_init_module js_init_module_qjsc_glfw
#endif

static inline JSAtom
js_iterator_atom(JSContext* ctx) {

  JSValue global_obj = JS_GetGlobalObject(ctx);
  JSValue symbol_ctor = JS_GetPropertyStr(ctx, global_obj, "Symbol");
  JSValue symbol_iterator = JS_GetPropertyStr(ctx, symbol_ctor, "iterator");
  JSAtom atom = JS_ValueToAtom(ctx, symbol_iterator);

  JS_FreeValue(ctx, global_obj);
  JS_FreeValue(ctx, symbol_ctor);
  JS_FreeValue(ctx, symbol_iterator);
  return atom;
}

JSModuleDef* js_init_module(JSContext* ctx, const char* module_name);

#endif
