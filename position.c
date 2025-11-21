#include "position.h"

void
glfw_position_read(JSContext* ctx, GLFWposition* pos, JSValueConst value) {
  JSValue x, y;

  if(JS_IsArray(ctx, value)) {
    x = JS_GetPropertyUint32(ctx, value, 0);
    y = JS_GetPropertyUint32(ctx, value, 1);
  } else {
    x = JS_GetPropertyStr(ctx, value, "x");
    y = JS_GetPropertyStr(ctx, value, "y");
  }

  int32_t tmp_x, tmp_y;
  JS_ToInt32(ctx, &tmp_x, x);
  JS_FreeValue(ctx, x);
  JS_ToInt32(ctx, &tmp_y, y);
  JS_FreeValue(ctx, y);

  pos->x = tmp_x;
  pos->y = tmp_y;
}

JSValue
glfw_position_write(JSContext* ctx, GLFWposition pos) {
  JSValue ret = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, ret, 0, JS_NewInt32(ctx, pos.x));
  JS_SetPropertyUint32(ctx, ret, 1, JS_NewInt32(ctx, pos.y));
  return ret;
}

void
glfw_position_f_read(JSContext* ctx, GLFWposition_f* pos, JSValueConst value) {
  GLFWposition_d tmp;

  glfw_position_f_read(ctx, &tmp, value);

  pos->x = tmp.x;
  pos->y = tmp.y;
}

JSValue
glfw_position_f_write(JSContext* ctx, GLFWposition_f pos) {
  return glfw_position_d_write(ctx, (GLFWposition_d){pos.x, pos.y});
}

void
glfw_position_d_read(JSContext* ctx, GLFWposition_d* pos, JSValueConst value) {
  JSValue x, y;

  if(JS_IsArray(ctx, value)) {
    x = JS_GetPropertyUint32(ctx, value, 0);
    y = JS_GetPropertyUint32(ctx, value, 1);
  } else {
    x = JS_GetPropertyStr(ctx, value, "x");
    y = JS_GetPropertyStr(ctx, value, "y");
  }

  JS_ToFloat64(ctx, &pos->x, x);
  JS_FreeValue(ctx, x);
  JS_ToFloat64(ctx, &pos->y, y);
  JS_FreeValue(ctx, y);
}

JSValue
glfw_position_d_write(JSContext* ctx, GLFWposition_d pos) {
  JSValue ret = JS_NewArray(ctx);
  JS_SetPropertyUint32(ctx, ret, 0, JS_NewFloat64(ctx, pos.x));
  JS_SetPropertyUint32(ctx, ret, 1, JS_NewFloat64(ctx, pos.y));
  return ret;
}
