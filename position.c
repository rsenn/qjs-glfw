#include "glfw.h"
#include "position.h"

thread_local JSClassID glfw_position_class_id = 0;
thread_local JSValue glfw_position_proto, glfw_position_class;

// constructor/destructor
static JSValue
glfw_position_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  GLFWposition *position, *other;

  if(!(position = js_mallocz(ctx, sizeof(GLFWposition))))
    return JS_EXCEPTION;

  if(JS_IsObject(argv[0]) && (other = JS_GetOpaque(argv[0], glfw_position_class_id))) {
    *position = *other;
  } else {
    int32_t x,y;

    if(JS_ToInt32(ctx, &x, argv[0])){ 
        JS_ThrowTypeError(ctx, "argument 1 (x-position) must be a number");
      goto fail;
    }

    if(JS_ToInt32(ctx, &y, argv[1])){ 
        JS_ThrowTypeError(ctx, "argument 2 (y-position) must be a number");
      goto fail;
    }

    position->x=x;
    position->y=y;
   }

  return glfw_position_wrap(ctx, position);

fail:
  js_free(ctx, position);
  return JS_EXCEPTION;
}

static void
glfw_position_finalizer(JSRuntime* rt, JSValue val) {
  GLFWposition* position;

  if((position = JS_GetOpaque(val, glfw_position_class_id)))
    js_free_rt(rt, position);
}

// properties
static JSValue
glfw_position_get(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWposition* position;

  if(!(position = JS_GetOpaque2(ctx, this_val, glfw_position_class_id)))
    return JS_EXCEPTION;

  return JS_NewInt32(ctx, magic == 0 ? position->x : position->y);
}

static JSValue
glfw_position_set(JSContext* ctx, JSValueConst this_val, JSValue val, int magic) {
  GLFWposition* position;

  if(!(position = JS_GetOpaque2(ctx, this_val, glfw_position_class_id)))
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
glfw_position_iterator(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWposition* position;
  JSValue arr, global_obj, symbol_constructor, symbol_iterator, iter, generator = JS_UNDEFINED;
  JSAtom atom;

  if(!(position = JS_GetOpaque2(ctx, this_val, glfw_position_class_id)))
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
static JSClassDef glfw_position_class_def = {
    .class_name = "Position",
    .finalizer = glfw_position_finalizer,
};

static const JSCFunctionListEntry glfw_position_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("x", glfw_position_get, glfw_position_set, 0),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("y", glfw_position_get, glfw_position_set, 1),
    JS_CFUNC_DEF("[Symbol.iterator]", 0, glfw_position_iterator),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWposition", JS_PROP_CONFIGURABLE),
};

JSValue
glfw_position_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_position_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_position_class_id, &glfw_position_class_def);

  glfw_position_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_position_proto, glfw_position_proto_funcs, countof(glfw_position_proto_funcs));
  JS_SetClassProto(ctx, glfw_position_class_id, glfw_position_proto);

  glfw_position_class = JS_NewCFunction2(ctx, glfw_position_constructor, "Position", 2, JS_CFUNC_constructor, 0);
  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_position_class, glfw_position_proto);

  JS_SetModuleExport(ctx, m, "Position", glfw_position_class);
}

JSValue
glfw_position_wrap(JSContext* ctx, GLFWposition* position) {
  JSValue obj = JS_UNDEFINED;
  JSValue proto;

  proto = JS_GetPropertyStr(ctx, glfw_position_class, "prototype");
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
glfw_position_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Position");
}
