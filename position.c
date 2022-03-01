#include "glfw.h"

#include "position.h"

JSClassID glfw_position_class_id = 0;

// constructor/destructor
JSValue
glfw_position_ctor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv) {
  GLFWPosition* position = js_mallocz(ctx, sizeof(*position));
  if(!position)
    return JS_EXCEPTION;

  if(JS_ToInt32(ctx, &position->x, argv[0]))
    goto fail;

  if(JS_ToInt32(ctx, &position->y, argv[1]))
    goto fail;

  return glfw_position_new_instance(ctx, position);
fail:
  js_free(ctx, position);
  return JS_EXCEPTION;
}

void
glfw_position_finalizer(JSRuntime* rt, JSValue val) {
  GLFWPosition* position = JS_GetOpaque(val, glfw_position_class_id);
  js_free_rt(rt, position);
}

// properties
JSValue
glfw_position_get_xy(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWPosition* position = JS_GetOpaque2(ctx, this_val, glfw_position_class_id);
  if(!position)
    return JS_EXCEPTION;
  return JS_NewInt32(ctx, magic == 0 ? position->x : position->y);
}

JSValue
glfw_position_set_xy(JSContext* ctx, JSValueConst this_val, JSValue val, int magic) {
  GLFWPosition* position = JS_GetOpaque2(ctx, this_val, glfw_position_class_id);
  if(!position)
    return JS_EXCEPTION;

  int value;
  if(JS_ToInt32(ctx, &value, val))
    return JS_EXCEPTION;

  if(magic == 0)
    position->x = value;
  else
    position->y = value;

  return JS_UNDEFINED;
}

static JSValue
glfw_position_iterator(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  JSValue arr, global_obj, symbol_ctor, symbol_iterator, iter, generator = JS_UNDEFINED;
  JSAtom atom;
  GLFWPosition* position = JS_GetOpaque2(ctx, this_val, glfw_position_class_id);
  if(!position)
    return JS_EXCEPTION;

  arr = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, arr, 0, JS_NewInt32(ctx, position->x));
  JS_SetPropertyUint32(ctx, arr, 1, JS_NewInt32(ctx, position->y));

  atom = js_iterator_atom(ctx);
  iter = JS_GetProperty(ctx, arr, atom);
  JS_FreeAtom(ctx, atom);

  if(JS_IsFunction(ctx, iter))
    generator = JS_Call(ctx, iter, arr, 0, 0);

  JS_FreeValue(ctx, iter);
  JS_FreeValue(ctx, arr);

  return generator;
}

// initialization
JSClassDef glfw_position_class_def = {
    "Position",
    .finalizer = glfw_position_finalizer,
};

const JSCFunctionListEntry glfw_position_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("x", glfw_position_get_xy, glfw_position_set_xy, 0),
    JS_CGETSET_MAGIC_DEF("y", glfw_position_get_xy, glfw_position_set_xy, 1),
    JS_CFUNC_DEF("[Symbol.iterator]", 0, glfw_position_iterator),
};

JSValue glfw_position_proto, glfw_position_class;

JSValue
glfw_position_constructor(JSContext* ctx) {
  JSRuntime* rt = JS_GetRuntime(ctx);

  if(!JS_IsRegisteredClass(rt, glfw_position_class_id)) {
    JS_NewClassID(&glfw_position_class_id);
    JS_NewClass(rt, glfw_position_class_id, &glfw_position_class_def);

    glfw_position_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, glfw_position_proto, glfw_position_proto_funcs, countof(glfw_position_proto_funcs));
    JS_SetClassProto(ctx, glfw_position_class_id, glfw_position_proto);

    glfw_position_class = JS_NewCFunction2(ctx, glfw_position_ctor, "Position", 2, JS_CFUNC_constructor, 0);
    /* set proto.constructor and ctor.prototype */
    JS_SetConstructor(ctx, glfw_position_class, glfw_position_proto);
  }

  return glfw_position_class;
}

JSValue
glfw_position_new_instance(JSContext* ctx, GLFWPosition* position) {
  JSValue obj = JS_UNDEFINED;
  JSValue proto;

  proto = JS_GetPropertyStr(ctx, glfw_position_constructor(ctx), "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_position_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, position);

  return obj;
fail:
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

int
glfw_position_init(JSContext* ctx, JSModuleDef* m) {
  JS_SetModuleExport(ctx, m, "Position", glfw_position_constructor(ctx));
  return 0;
}

int
glfw_position_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Position");
}
