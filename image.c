#include "glfw.h"
#include "image.h"
#include "size.h"
#include <assert.h>
#include <string.h>

JSClassID glfw_image_class_id = 0;
JSValue glfw_image_proto, glfw_image_class;

static void
image_free(GLFWimage* img) {
  if(img->pixels)
    free(img->pixels);

  free(img);
}

static GLFWimage*
image_new(int width, int height) {
  GLFWimage* ret;

  if((ret = malloc(sizeof(GLFWimage)))) {
    ret->width = width;
    ret->height = height;

    if(!(ret->pixels = calloc(width * height, 4))) {
      image_free(ret);
      return 0;
    }
  }

  return ret;
}

static GLFWimage*
image_clone(GLFWimage const* img) {
  const size_t len = 4 * img->width * img->height;
  GLFWimage* ret;

  if((ret = malloc(sizeof(GLFWimage)))) {
    ret->pixels = NULL;
    ret->width = img->width;
    ret->height = img->height;

    if(!(ret->pixels = malloc(len))) {
      image_free(ret);
      return 0;
    }

    memcpy(ret->pixels, img->pixels, len);
  }

  return ret;
}

static void
image_unref(JSRuntime* rt, void* opaque, void* ptr) {
  JSObject* obj = opaque;
  JSValue image = JS_MKPTR(JS_TAG_OBJECT, obj);

  JS_FreeValueRT(rt, image);
}

// properties
static JSValue
glfw_image_buffer(JSContext* ctx, JSValueConst value) {
  GLFWimage* image = JS_GetOpaque(value, glfw_image_class_id);

  return JS_NewArrayBuffer(ctx, (uint8_t*)image->pixels, image->width * image->height * 4, image_unref, JS_VALUE_GET_PTR(JS_DupValue(ctx, value)), FALSE);
}

// properties
static JSValue
create_typedarray(JSContext* ctx, const char* type, JSValueConst buffer, uint32_t offset, uint32_t count) {
  JSValue args[3] = {
      buffer,
      JS_NewUint32(ctx, offset),
      JS_NewUint32(ctx, count),
  };

  JSValue global = JS_GetGlobalObject(ctx);
  JSValue ctor = JS_GetPropertyStr(ctx, global, type);
  JS_FreeValue(ctx, global);
  JSValue ret = JS_CallConstructor(ctx, ctor, count > 0 && count != UINT32_MAX ? 3 : 2, args);
  JS_FreeValue(ctx, ctor);

  JS_FreeValue(ctx, args[1]);
  JS_FreeValue(ctx, args[2]);

  return ret;
}

// constructor/destructor
static JSValue
glfw_image_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  GLFWimage* image = 0;
  GLFWsize* size;
  uint32_t width, height;
  JSValue proto, obj = JS_UNDEFINED;

  if(JS_IsObject(argv[0]) && (size = JS_GetOpaque(argv[0], glfw_size_class_id))) {
    width = size->width;
    height = size->height;
  } else {

    if(JS_ToUint32(ctx, &width, argv[0])) {
      JS_ThrowTypeError(ctx, "argument 1 (width) must be a number");
      goto fail;
    }

    if(JS_ToUint32(ctx, &height, argv[1])) {
      JS_ThrowTypeError(ctx, "argument 2 (height) must be a number");
      goto fail;
    }
  }

  if(!(image = image_new(width, height)))
    return JS_EXCEPTION;

  /* using new_target to get the prototype is necessary when the class is extended. */
  proto = JS_GetPropertyStr(ctx, new_target, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_image_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, image);
  return obj;

fail:
  if(image)
    js_free(ctx, image);
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

enum {
  IMAGE_PIXELS,
};

// properties
static JSValue
glfw_image_array(JSContext* ctx, JSValueConst this_val) {
  GLFWimage* image;

  if(!(image = JS_GetOpaque2(ctx, this_val, glfw_image_class_id)))
    return JS_EXCEPTION;

  JSValue buf = glfw_image_buffer(ctx, this_val);
  JSValue ret = create_typedarray(ctx, "Uint32Array", buf, 0, UINT32_MAX);
  JS_FreeValue(ctx, buf);

  return ret;
}

enum {
  IMAGE_WIDTH,
  IMAGE_HEIGHT,
};

// properties
static JSValue
glfw_image_get(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWimage* image;
  JSValue ret = JS_UNDEFINED;

  if(!(image = JS_GetOpaque2(ctx, this_val, glfw_image_class_id)))
    return JS_EXCEPTION;

  switch(magic) {
    case IMAGE_WIDTH: {
      ret = JS_NewUint32(ctx, image->width);
      break;
    }

    case IMAGE_HEIGHT: {
      ret = JS_NewUint32(ctx, image->height);
      break;
    }
  }

  return ret;
}

static void
glfw_image_finalizer(JSRuntime* rt, JSValue val) {
  GLFWimage* image;

  if((image = JS_GetOpaque(val, glfw_image_class_id)))
    image_free(image);
}

static int
glfw_image_get_own_property(JSContext* ctx, JSPropertyDescriptor* pdesc, JSValueConst obj, JSAtom atom) {
  GLFWimage* image;
  JSValue prop;
  int32_t row = -1;

  if(!(image = JS_GetOpaque2(ctx, obj, glfw_image_class_id)))
    return FALSE;

  prop = JS_AtomToValue(ctx, atom);
  JS_ToInt32(ctx, &row, prop);

  printf("%s prop=%s row=%li\n", __func__, JS_ToCString(ctx, prop), (long int)row);

  if(pdesc && row >= 0 && row < image->height) {
    JSValue buf = glfw_image_buffer(ctx, obj);

    if(pdesc) {
      pdesc->flags = 0;
      pdesc->value = create_typedarray(ctx, "Uint32Array", buf, image->width * row * 4, image->width);
      pdesc->getter = JS_UNDEFINED;
      pdesc->setter = JS_UNDEFINED;
    }

    JS_FreeValue(ctx, buf);

    return TRUE;
  }

  return FALSE;
}

static JSClassExoticMethods glfw_image_exotic_methods = {
    .get_own_property = glfw_image_get_own_property,
};

// initialization
static JSClassDef glfw_image_class_def = {
    .class_name = "Image", .finalizer = glfw_image_finalizer,
    //.exotic = &glfw_image_exotic_methods,
};

static const JSCFunctionListEntry glfw_image_proto_funcs[] = {
    JS_CGETSET_DEF("pixels", glfw_image_array, NULL),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("width", glfw_image_get, NULL, IMAGE_WIDTH),
    JS_CGETSET_ENUMERABLE_MAGIC_DEF("height", glfw_image_get, NULL, IMAGE_HEIGHT),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWimage", JS_PROP_CONFIGURABLE),
};

int
glfw_image_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_image_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_image_class_id, &glfw_image_class_def);

  glfw_image_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_image_proto, glfw_image_proto_funcs, countof(glfw_image_proto_funcs));
  JS_SetClassProto(ctx, glfw_image_class_id, glfw_image_proto);

  glfw_image_class = JS_NewCFunction2(ctx, glfw_image_constructor, "Image", 2, JS_CFUNC_constructor, 0);
  /* set proto.constructor and ctor.prototype */
  JS_SetConstructor(ctx, glfw_image_class, glfw_image_proto);
  JS_SetModuleExport(ctx, m, "Image", glfw_image_class);
  return 0;
}

JSValue
glfw_image_wrap(JSContext* ctx, const GLFWimage* img) {
  JSValue obj, proto = JS_GetPropertyStr(ctx, glfw_image_class, "prototype");
  GLFWimage* image;

  if(!(image = image_clone(img)))
    return JS_EXCEPTION;

  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, proto);
    return JS_EXCEPTION;
  }

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_image_class_id);
  JS_FreeValue(ctx, proto);

  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
  }

  JS_SetOpaque(obj, image);
  return obj;
}

int
glfw_image_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Image");
}
