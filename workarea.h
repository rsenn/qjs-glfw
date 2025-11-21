#ifndef GLFW_MODULE_WORKAREA
#define GLFW_MODULE_WORKAREA 1

#include "position.h"
#include "size.h"

typedef struct {
  GLFWposition_i position;
  GLFWsize size;
} GLFWworkarea;

void glfw_workarea_read(JSContext*, GLFWworkarea*, JSValueConst);
JSValue glfw_workarea_write(JSContext*, GLFWworkarea);

#endif
