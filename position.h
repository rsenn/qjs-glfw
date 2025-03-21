#ifndef GLFW_MODULE_POSITION
#define GLFW_MODULE_POSITION 1

#include "glfw.h"
typedef struct {
  int x, y;
} GLFWposition;

extern JSClassID glfw_position_class_id;
extern JSValue glfw_position_proto, glfw_position_class;

int glfw_position_init(JSContext*, JSModuleDef*);
JSValue glfw_position_wrap(JSContext*, GLFWposition*);
int glfw_position_export(JSContext*, JSModuleDef*);

#endif
