#include "glfw.h"
#include "workarea.h"

void
glfw_workarea_read(JSContext* ctx, GLFWworkarea* workarea, JSValueConst value) {
  JSValue x, y, width, height;

  if(JS_IsArray(ctx, value)) {
    x = JS_GetPropertyUint32(ctx, value, 0);
    y = JS_GetPropertyUint32(ctx, value, 1);
    width = JS_GetPropertyUint32(ctx, value, 2);
    height = JS_GetPropertyUint32(ctx, value, 3);
  } else {
    x = JS_GetPropertyStr(ctx, value, "x");
    y = JS_GetPropertyStr(ctx, value, "y");
    width = JS_GetPropertyStr(ctx, value, "width");
    height = JS_GetPropertyStr(ctx, value, "height");
  }

  int32_t tmp_x, tmp_y, tmp_width, tmp_height;

  JS_ToInt32(ctx, &tmp_x, x);
  JS_FreeValue(ctx, x);
  JS_ToInt32(ctx, &tmp_y, y);
  JS_FreeValue(ctx, y);
  JS_ToInt32(ctx, &tmp_width, width);
  JS_FreeValue(ctx, width);
  JS_ToInt32(ctx, &tmp_height, height);
  JS_FreeValue(ctx, height);

  pos->x = tmp_x;
  pos->y = tmp_y;
  pos->width = tmp_width;
  pos->height = tmp_height;
}

JSValue
glfw_workarea_write(JSContext* ctx, GLFWworkarea workarea) {
  JSValue ret = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, ret, 0, JS_NewInt32(ctx, workarea.x));
  JS_SetPropertyUint32(ctx, ret, 1, JS_NewInt32(ctx, workarea.y));
  JS_SetPropertyUint32(ctx, ret, 2, JS_NewInt32(ctx, workarea.width));
  JS_SetPropertyUint32(ctx, ret, 3, JS_NewInt32(ctx, workarea.height));
  return ret;
}
