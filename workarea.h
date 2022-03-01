#ifndef GLFW_MODULE_WORKAREA
#define GLFW_MODULE_WORKAREA 1

#include "position.h"
#include "size.h"

typedef struct {
  GLFWposition* position;
  GLFWsize* size;
} GLFWworkarea;

extern JSClassID glfw_workarea_class_id;
JSValue glfw_workarea_new_instance(JSContext* ctx, GLFWworkarea* workarea);
int glfw_workarea_init(JSContext* ctx, JSModuleDef* m);
int glfw_workarea_export(JSContext* ctx, JSModuleDef* m);

#endif
