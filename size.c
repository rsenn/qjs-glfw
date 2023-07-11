#include "glfw.h"
#include "size.h"

thread_local JSClassID glfw_size_class_id = 0;
thread_local JSValue glfw_size_proto, glfw_size_class;

// constructor/destructor
static JSValue
glfw_size_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  GLFWsize *size, *other;
  JSValue proto, obj = JS_UNDEFINED;

  if(!(size = js_mallocz(ctx, sizeof(*size))))
    return JS_EXCEPTION;

  if(JS_IsObject(argv[0]) && (other = JS_GetOpaque(argv[0], glfw_size_class_id))) {
    *size = *other;
  } else {
    uint32_t w, h;

    if(JS_ToUint32(ctx, &w, argv[0])) {
      JS_ThrowTypeError(ctx, "argument 1 (width) must be a number");
      goto fail;
    }
    if(JS_ToUint32(ctx, &h, argv[1])) {
      JS_ThrowTypeError(ctx, "argument 2 (height) must be a number");
      goto fail;
    }

    size->width = w;
    size->height = h;
  }

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_size_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, size);
  return obj;

fail:
  js_free(ctx, size);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

static void
glfw_size_finalizer(JSRuntime* rt, JSValue val) {
  GLFWsize* size;

  if((size = JS_GetOpaque(val, glfw_size_class_id)))
    js_free_rt(rt, size);
}

// properties
static JSValue
glfw_size_get(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWsize* size;

  if(!(size = JS_GetOpaque2(ctx, this_val, glfw_size_class_id)))
    return JS_EXCEPTION;

  return JS_NewInt32(ctx, magic == 0 ? size->width : size->height);
}

static JSValue
glfw_size_set(JSContext* ctx, JSValueConst this_val, JSValue val, int magic) {
  GLFWsize* size;

  if(!(size = JS_GetOpaque2(ctx, this_val, glfw_size_class_id)))
    return JS_EXCEPTION;

  int value;
  if(JS_ToInt32(ctx, &value, val))
    return JS_EXCEPTION;

  if(magic == 0)
    size->width = value;
  else
    size->height = value;

  return JS_UNDEFINED;
}

static JSValue
glfw_size_iterator(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWsize* size;
  JSValue arr, global_obj, symbol_constructor, symbol_iterator, iter, generator = JS_UNDEFINED;
  JSAtom atom;

  if(!(size = JS_GetOpaque2(ctx, this_val, glfw_size_class_id)))
    return JS_EXCEPTION;

  arr = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, arr, 0, JS_NewInt32(ctx, size->width));
  JS_SetPropertyUint32(ctx, arr, 1, JS_NewInt32(ctx, size->height));

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
static JSClassDef glfw_size_class_def = {
    .class_name = "Size",
    .finalizer = glfw_size_finalizer,
};

static const JSCFunctionListEntry glfw_size_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("width", glfw_size_get, glfw_size_set, 0),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("height", glfw_size_get, glfw_size_set, 1),
    JS_CFUNC_DEF("[Symbol.iterator]", 0, glfw_size_iterator),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWsize", JS_PROP_CONFIGURABLE),
};

int
glfw_size_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_size_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_size_class_id, &glfw_size_class_def);

  glfw_size_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_size_proto, glfw_size_proto_funcs, countof(glfw_size_proto_funcs));
  JS_SetClassProto(ctx, glfw_size_class_id, glfw_size_proto);

  glfw_size_class = JS_NewCFunction2(ctx, glfw_size_constructor, "Size", 2, JS_CFUNC_constructor, 0);

  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_size_class, glfw_size_proto);

  JS_SetModuleExport(ctx, m, "Size", glfw_size_class);
  return 0;
}

JSValue
glfw_size_wrap(JSContext* ctx, GLFWsize* size) {
  JSValue obj = JS_UNDEFINED;
  JSValue proto;

  proto = JS_GetPropertyStr(ctx, glfw_size_class, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_size_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, size);

  return obj;
fail:
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

int
glfw_size_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Size");
}
