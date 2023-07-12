#include "glfw.h"
#include "gamma_ramp.h"
#include <string.h>

thread_local JSClassID glfw_gamma_ramp_class_id = 0;
thread_local JSValue glfw_gamma_ramp_proto, glfw_gamma_ramp_class;

static void
gamma_ramp_free(GLFWgammaramp* gr) {
  if(gr->red)
    free(gr->red);
  if(gr->green)
    free(gr->green);
  if(gr->blue)
    free(gr->blue);

  free(gr);
}

static GLFWgammaramp*
gamma_ramp_clone(GLFWgammaramp const* gr) {
  const size_t len = sizeof(unsigned short) * gr->size;
  GLFWgammaramp* ret;

  if((ret = malloc(sizeof(GLFWgammaramp)))) {
    ret->red = ret->green = ret->blue = NULL;
    ret->size = gr->size;

    if(!(ret->red = malloc(len)) || !(ret->green = malloc(len)) || !(ret->blue = malloc(len))) {
      gamma_ramp_free(ret);
      return 0;
    }

    memcpy(ret->red, gr->red, len);
    memcpy(ret->green, gr->green, len);
    memcpy(ret->blue, gr->blue, len);
  }

  return ret;
}

// constructor/destructor
static JSValue
glfw_gamma_ramp_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JS_ThrowInternalError(ctx, "glfw.GammaRamp can not be constructed directly");
  return JS_EXCEPTION;
}

static void
gamma_ramp_unref(JSRuntime* rt, void* opaque, void* ptr) {
  JSObject* obj = opaque;
  JSValue gamma_ramp = JS_MKPTR(JS_TAG_OBJECT, obj);

  JS_FreeValueRT(rt, gamma_ramp);
}

enum {
  GAMMA_RED,
  GAMMA_GREEN,
  GAMMA_BLUE,
};

// properties
static JSValue
glfw_gamma_ramp_array(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWgammaramp* gamma_ramp;
  unsigned short* ptr;
  JSValue global, ctor, buf, ret;

  if(!(gamma_ramp = JS_GetOpaque2(ctx, this_val, glfw_gamma_ramp_class_id)))
    return JS_EXCEPTION;

  switch(magic) {
    case GAMMA_RED: ptr = gamma_ramp->red; break;
    case GAMMA_GREEN: ptr = gamma_ramp->green; break;
    case GAMMA_BLUE: ptr = gamma_ramp->blue; break;
  }

  buf = JS_NewArrayBuffer(ctx, (uint8_t*)ptr, sizeof(*ptr) * gamma_ramp->size, gamma_ramp_unref, JS_VALUE_GET_PTR(JS_DupValue(ctx, this_val)), FALSE);

  global = JS_GetGlobalObject(ctx);
  ctor = JS_GetPropertyStr(ctx, global, "Uint16Array");
  JS_FreeValue(ctx, global);
  ret = JS_CallConstructor(ctx, ctor, 1, &buf);
  JS_FreeValue(ctx, ctor);
  JS_FreeValue(ctx, buf);

  return ret;
}

// properties
static JSValue
glfw_gamma_ramp_size(JSContext* ctx, JSValueConst this_val) {
  GLFWgammaramp* gamma_ramp;

  if(!(gamma_ramp = JS_GetOpaque2(ctx, this_val, glfw_gamma_ramp_class_id)))
    return JS_EXCEPTION;

  return JS_NewUint32(ctx, gamma_ramp->size);
}

static void
glfw_gamma_ramp_finalizer(JSRuntime* rt, JSValue val) {
  GLFWgammaramp* gamma_ramp;

  if((gamma_ramp = JS_GetOpaque(val, glfw_gamma_ramp_class_id)))
    gamma_ramp_free(gamma_ramp);
}

// initialization
static JSClassDef glfw_gamma_ramp_class_def = {
    .class_name = "GammaRamp",
    .finalizer = glfw_gamma_ramp_finalizer,
};

static const JSCFunctionListEntry glfw_gamma_ramp_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("red", glfw_gamma_ramp_array, NULL, GAMMA_RED),
    JS_CGETSET_MAGIC_DEF("green", glfw_gamma_ramp_array, NULL, GAMMA_GREEN),
    JS_CGETSET_MAGIC_DEF("blue", glfw_gamma_ramp_array, NULL, GAMMA_BLUE),
    JS_CGETSET_ENUMERABLE_DEF("size", glfw_gamma_ramp_size, NULL),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWgammaramp", JS_PROP_CONFIGURABLE),
};

int
glfw_gamma_ramp_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_gamma_ramp_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_gamma_ramp_class_id, &glfw_gamma_ramp_class_def);

  glfw_gamma_ramp_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_gamma_ramp_proto, glfw_gamma_ramp_proto_funcs, countof(glfw_gamma_ramp_proto_funcs));
  JS_SetClassProto(ctx, glfw_gamma_ramp_class_id, glfw_gamma_ramp_proto);

  glfw_gamma_ramp_class = JS_NewCFunction2(ctx, glfw_gamma_ramp_constructor, "GammaRamp", 2, JS_CFUNC_constructor, 0);
  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_gamma_ramp_class, glfw_gamma_ramp_proto);
  JS_SetModuleExport(ctx, m, "GammaRamp", glfw_gamma_ramp_class);
  return 0;
}

JSValue
glfw_gamma_ramp_wrap(JSContext* ctx, const GLFWgammaramp* gr) {
  JSValue obj, proto = JS_GetPropertyStr(ctx, glfw_gamma_ramp_class, "prototype");
  GLFWgammaramp* gamma_ramp;

  if(!(gamma_ramp = gamma_ramp_clone(gr)))
    return JS_EXCEPTION;

  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, proto);
    return JS_EXCEPTION;
  }

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_gamma_ramp_class_id);
  JS_FreeValue(ctx, proto);

  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
  }

  JS_SetOpaque(obj, gamma_ramp);
  return obj;
}

int
glfw_gamma_ramp_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "GammaRamp");
}
