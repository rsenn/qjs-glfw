#include "glfw.h"

void
glfw_size_read(JSContext* ctx, GLFWsize* pos, JSValueConst value) {
  JSValue width, height;

  if(JS_IsArray(ctx, value)) {
    width = JS_GetPropertyUint32(ctx, value, 0);
    height = JS_GetPropertyUint32(ctx, value, 1);
  } else {
    width = JS_GetPropertyStr(ctx, value, "width");
    height = JS_GetPropertyStr(ctx, value, "height");
  }

  int32_t w, h;
  JS_ToInt32(ctx, &w, width);
  JS_FreeValue(ctx, width);
  JS_ToInt32(ctx, &h, height);
  JS_FreeValue(ctx, height);

  pos->width = w;
  pos->height = h;
}

JSValue
glfw_size_write(JSContext* ctx, GLFWsize pos) {
  JSValue ret = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, ret, 0, JS_NewInt32(ctx, pos.width));
  JS_SetPropertyUint32(ctx, ret, 1, JS_NewInt32(ctx, pos.height));
  return ret;
}
