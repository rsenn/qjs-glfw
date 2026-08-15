#ifndef QJS_GLFW_WORKAREA_H
#define QJS_GLFW_WORKAREA_H 1

#include "position.h"
#include "size.h"

typedef struct {
  GLFWposition* position;
  GLFWsize* size;
} GLFWworkarea;

extern JSClassID glfw_workarea_class_id;
extern JSValue glfw_workarea_proto, glfw_workarea_class;

int glfw_workarea_init(JSContext*, JSModuleDef*);
JSValue glfw_workarea_wrap(JSContext*, GLFWworkarea*);
int glfw_workarea_export(JSContext*, JSModuleDef*);

#endif
