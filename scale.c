#include "glfw.h"
#include "scale.h"

JSClassID glfw_scale_class_id = 0;
JSValue glfw_scale_proto, glfw_scale_class;

// constructor/destructor
static JSValue
glfw_scale_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  GLFWscale *scale, *other;
  JSValue proto, obj = JS_UNDEFINED;

  if(!(scale = js_mallocz(ctx, sizeof(*scale))))
    return JS_EXCEPTION;

  if(JS_IsObject(argv[0]) && (other = JS_GetOpaque(argv[0], glfw_scale_class_id))) {
    *scale = *other;
  } else {
    if(JS_ToFloat64(ctx, &scale->x, argv[0])) {
      JS_ThrowTypeError(ctx, "argument 1 (x-scaling) must be a number");
      goto fail;
    }

    if(JS_ToFloat64(ctx, &scale->y, argv[1])) {
      JS_ThrowTypeError(ctx, "argument 2 (y-scaling) must be a number");
      goto fail;
    }
  }

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_scale_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, scale);
  return obj;
fail:
  js_free(ctx, scale);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

void static glfw_scale_finalizer(JSRuntime* rt, JSValue val) {
  GLFWscale* scale;

  if((scale = JS_GetOpaque(val, glfw_scale_class_id)))
    js_free_rt(rt, scale);
}

// properties
static JSValue
glfw_scale_get(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWscale* scale;

  if(!(scale = JS_GetOpaque2(ctx, this_val, glfw_scale_class_id)))
    return JS_EXCEPTION;

  return JS_NewFloat64(ctx, magic == 0 ? scale->x : scale->y);
}

static JSValue
glfw_scale_set(JSContext* ctx, JSValueConst this_val, JSValue val, int magic) {
  GLFWscale* scale;

  if(!(scale = JS_GetOpaque2(ctx, this_val, glfw_scale_class_id)))
    return JS_EXCEPTION;

  double value;
  if(JS_ToFloat64(ctx, &value, val))
    return JS_EXCEPTION;

  if(magic == 0)
    scale->x = value;
  else
    scale->y = value;

  return JS_UNDEFINED;
}

static JSValue
glfw_scale_iterator(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWscale* scale;
  JSValue arr, iter, generator = JS_UNDEFINED;
  JSAtom atom;

  if(!(scale = JS_GetOpaque2(ctx, this_val, glfw_scale_class_id)))
    return JS_EXCEPTION;

  arr = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, arr, 0, JS_NewInt32(ctx, scale->x));
  JS_SetPropertyUint32(ctx, arr, 1, JS_NewInt32(ctx, scale->y));

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
static JSClassDef glfw_scale_class_def = {
    .class_name = "Scale",
    .finalizer = glfw_scale_finalizer,
};

static const JSCFunctionListEntry glfw_scale_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("x", glfw_scale_get, glfw_scale_set, 0),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("y", glfw_scale_get, glfw_scale_set, 1),
    JS_CFUNC_DEF("[Symbol.iterator]", 0, glfw_scale_iterator),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWscale", JS_PROP_CONFIGURABLE),
};

int
glfw_scale_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_scale_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_scale_class_id, &glfw_scale_class_def);

  glfw_scale_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_scale_proto, glfw_scale_proto_funcs, countof(glfw_scale_proto_funcs));
  JS_SetClassProto(ctx, glfw_scale_class_id, glfw_scale_proto);

  glfw_scale_class = JS_NewCFunction2(ctx, glfw_scale_constructor, "Scale", 2, JS_CFUNC_constructor, 0);
  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_scale_class, glfw_scale_proto);

  JS_SetModuleExport(ctx, m, "Scale", glfw_scale_class);
  return 0;
}

JSValue
glfw_scale_wrap(JSContext* ctx, GLFWscale* scale) {
  JSValue obj = JS_UNDEFINED;
  JSValue proto;

  proto = JS_GetPropertyStr(ctx, glfw_scale_class, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_scale_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, scale);

  return obj;
fail:
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

int
glfw_scale_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Scale");
}
