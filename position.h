#ifndef GLFW_MODULE_POSITION
#define GLFW_MODULE_POSITION 1

#include "glfw.h"

typedef struct {
  int x, y;
} GLFWposition;

void glfw_position_read(JSContext*, GLFWposition*, JSValueConst);
JSValue glfw_position_write(JSContext*, GLFWposition);

typedef struct {
  float x, y;
} GLFWposition_f;

void glfw_position_f_read(JSContext*, GLFWposition_f*, JSValueConst);
JSValue glfw_position_f_write(JSContext*, GLFWposition_f);

typedef struct {
  double x, y;
} GLFWposition_d;

void glfw_position_d_read(JSContext*, GLFWposition_d*, JSValueConst);
JSValue glfw_position_d_write(JSContext*, GLFWposition_d);

#endif
