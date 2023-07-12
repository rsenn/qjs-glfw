#include "glfw.h"
#include "workarea.h"

thread_local JSClassID glfw_workarea_class_id = 0;
thread_local JSValue glfw_workarea_proto, glfw_workarea_class;

// constructor/destructor
static JSValue
glfw_workarea_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  GLFWworkarea* workarea;
  GLFWposition* position;
  GLFWsize* size;
  int i = 0;

  if(!(workarea = js_mallocz(ctx, sizeof(*workarea))))
    return JS_EXCEPTION;

  if(!(workarea->position = js_mallocz(ctx, sizeof(*position))))
    return JS_EXCEPTION;

  if(!(workarea->size = js_mallocz(ctx, sizeof(*size))))
    return JS_EXCEPTION;

  if(JS_IsObject(argv[i]) && (position = JS_GetOpaque(argv[i], glfw_position_class_id))) {
    *workarea->position = *position;

    ++i;
  } else {
    int32_t x, y;

    if(JS_ToInt32(ctx, &x, argv[i])) {
      JS_ThrowTypeError(ctx, "argument %d (x-position) must be a number", i + 1);
      goto fail;
    }

    if(JS_ToInt32(ctx, &y, argv[i + 1])) {
      JS_ThrowTypeError(ctx, "argument %d (y-position) must be a number", i + 2);
      goto fail;
    }

    workarea->position->x = x;
    workarea->position->y = y;

    i += 2;
  }

  if(JS_IsObject(argv[i]) && (size = JS_GetOpaque(argv[i], glfw_size_class_id))) {
    *workarea->size = *size;
    ++i;
  } else {
    uint32_t w, h;

    if(JS_ToUint32(ctx, &w, argv[i])) {
      JS_ThrowTypeError(ctx, "argument %d (width) must be a number", i + 1);
      goto fail;
    }

    if(JS_ToUint32(ctx, &h, argv[i + 1])) {
      JS_ThrowTypeError(ctx, "argument %d (height) must be a number", i + 2);
      goto fail;
    }

    workarea->size->width = w;
    workarea->size->height = h;

    i += 2;
  }

  return glfw_workarea_wrap(ctx, workarea);

fail:
  js_free(ctx, workarea);
  return JS_EXCEPTION;
}

static void
glfw_workarea_finalizer(JSRuntime* rt, JSValue val) {
  GLFWworkarea* workarea;

  if((workarea = JS_GetOpaque(val, glfw_workarea_class_id)))
    js_free_rt(rt, workarea);
}

// properties
static JSValue
glfw_workarea_get(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWworkarea* workarea;

  if(!(workarea = JS_GetOpaque2(ctx, this_val, glfw_workarea_class_id)))
    return JS_EXCEPTION;

  return magic == 0 ? glfw_position_wrap(ctx, workarea->position) : glfw_size_wrap(ctx, workarea->size);
}

static JSValue
glfw_workarea_set(JSContext* ctx, JSValueConst this_val, JSValue val, int magic) {
  GLFWworkarea* workarea;

  if(!(workarea = JS_GetOpaque2(ctx, this_val, glfw_workarea_class_id)))
    return JS_EXCEPTION;

  if(magic == 0)
    workarea->position = JS_GetOpaque2(ctx, val, glfw_position_class_id);
  else
    workarea->size = JS_GetOpaque2(ctx, val, glfw_size_class_id);

  return JS_UNDEFINED;
}

static JSValue
glfw_workarea_iterator(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWworkarea* workarea;
  JSValue arr, iter, generator = JS_UNDEFINED;
  JSAtom atom;

  if(!(workarea = JS_GetOpaque2(ctx, this_val, glfw_workarea_class_id)))
    return JS_EXCEPTION;

  arr = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, arr, 0, JS_NewInt32(ctx, workarea->position->x));
  JS_SetPropertyUint32(ctx, arr, 1, JS_NewInt32(ctx, workarea->position->y));
  JS_SetPropertyUint32(ctx, arr, 2, JS_NewInt32(ctx, workarea->size->width));
  JS_SetPropertyUint32(ctx, arr, 3, JS_NewInt32(ctx, workarea->size->height));

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
static JSClassDef glfw_workarea_class_def = {
    .class_name = "WorkArea",
    .finalizer = glfw_workarea_finalizer,
};

static const JSCFunctionListEntry glfw_workarea_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("position", glfw_workarea_get, glfw_workarea_set, 0),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("size", glfw_workarea_get, glfw_workarea_set, 1),
    JS_CFUNC_DEF("[Symbol.iterator]", 0, glfw_workarea_iterator),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWworkarea", JS_PROP_CONFIGURABLE),
};

int
glfw_workarea_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_workarea_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_workarea_class_id, &glfw_workarea_class_def);

  glfw_workarea_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_workarea_proto, glfw_workarea_proto_funcs, countof(glfw_workarea_proto_funcs));
  JS_SetClassProto(ctx, glfw_workarea_class_id, glfw_workarea_proto);

  glfw_workarea_class = JS_NewCFunction2(ctx, glfw_workarea_constructor, "WorkArea", 2, JS_CFUNC_constructor, 0);

  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_workarea_class, glfw_workarea_proto);

  JS_SetModuleExport(ctx, m, "WorkArea", glfw_workarea_class);
  return 0;
}

JSValue
glfw_workarea_wrap(JSContext* ctx, GLFWworkarea* workarea) {
  JSValue proto = JS_GetPropertyStr(ctx, glfw_workarea_class, "prototype");
  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, proto);
    return JS_EXCEPTION;
  }

  JSValue obj = JS_NewObjectProtoClass(ctx, proto, glfw_workarea_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
  }

  JS_SetOpaque(obj, workarea);
  return obj;
}

int
glfw_workarea_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "WorkArea");
}
