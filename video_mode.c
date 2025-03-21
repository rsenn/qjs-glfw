#include "glfw.h"
#include "video_mode.h"

JSClassID glfw_video_mode_class_id = 0;
JSValue glfw_video_mode_proto, glfw_video_mode_class;

// constructor/destructor
static JSValue
glfw_video_mode_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  JS_ThrowInternalError(ctx, "VideoMode can not be constructed directly");
  return JS_EXCEPTION;
}

// properties
static JSValue
glfw_video_mode_get(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWvidmode* video_mode = JS_GetOpaque2(ctx, this_val, glfw_video_mode_class_id);
  if(!video_mode)
    return JS_EXCEPTION;

  int value;

  switch(magic) {
    case 0: value = video_mode->width; break;
    case 1: value = video_mode->height; break;
    case 2: value = video_mode->redBits; break;
    case 3: value = video_mode->greenBits; break;
    case 4: value = video_mode->blueBits; break;
    case 5: value = video_mode->refreshRate; break;
  }

  return JS_NewInt64(ctx, value);
}

static JSValue
glfw_video_mode_set(JSContext* ctx, JSValueConst this_val, JSValue val, int magic) {
  GLFWvidmode* video_mode = JS_GetOpaque2(ctx, this_val, glfw_video_mode_class_id);
  if(!video_mode)
    return JS_EXCEPTION;

  int value;
  if(JS_ToInt32(ctx, &value, val))
    return JS_EXCEPTION;

  switch(magic) {
    case 0: video_mode->width = value; break;
    case 1: video_mode->height = value; break;
    case 2: video_mode->redBits = value; break;
    case 3: video_mode->greenBits = value; break;
    case 4: video_mode->blueBits = value; break;
    case 5: video_mode->refreshRate = value; break;
  }

  return JS_UNDEFINED;
}

// initialization
JSClassDef glfw_video_mode_class_def = {
    .class_name = "VideoMode",
};

static const JSCFunctionListEntry glfw_video_mode_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("width", glfw_video_mode_get, glfw_video_mode_set, 0),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("height", glfw_video_mode_get, glfw_video_mode_set, 1),
    JS_CGETSET_MAGIC_DEF("redBits", glfw_video_mode_get, glfw_video_mode_set, 2),
    JS_CGETSET_MAGIC_DEF("greenBits", glfw_video_mode_get, glfw_video_mode_set, 3),
    JS_CGETSET_MAGIC_DEF("blueBits", glfw_video_mode_get, glfw_video_mode_set, 4),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("refreshRate", glfw_video_mode_get, glfw_video_mode_set, 5),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWvidmode", JS_PROP_CONFIGURABLE),
};

int
glfw_video_mode_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_video_mode_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_video_mode_class_id, &glfw_video_mode_class_def);

  glfw_video_mode_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_video_mode_proto, glfw_video_mode_proto_funcs, countof(glfw_video_mode_proto_funcs));
  JS_SetClassProto(ctx, glfw_video_mode_class_id, glfw_video_mode_proto);

  glfw_video_mode_class = JS_NewCFunction2(ctx, glfw_video_mode_constructor, "VideoMode", 2, JS_CFUNC_constructor, 0);
  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_video_mode_class, glfw_video_mode_proto);
  JS_SetModuleExport(ctx, m, "VideoMode", glfw_video_mode_class);
  return 0;
}

JSValue
glfw_video_mode_wrap(JSContext* ctx, const GLFWvidmode* video_mode) {
  JSValue proto = JS_GetPropertyStr(ctx, glfw_video_mode_class, "prototype");
  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, proto);
    return JS_EXCEPTION;
  }

  JSValue obj = JS_NewObjectProtoClass(ctx, proto, glfw_video_mode_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
  }

  JS_SetOpaque(obj, (void*)video_mode);
  return obj;
}

int
glfw_video_mode_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "VideoMode");
}
