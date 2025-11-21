#ifndef GLFW_MODULE_SIZE
#define GLFW_MODULE_SIZE 1

#include "glfw.h"

typedef struct {
  int width, height;
} GLFWsize;

void glfw_size_read(JSContext*, GLFWsize*, JSValueConst);
JSValue glfw_size_write(JSContext*, GLFWsize);

#endif
