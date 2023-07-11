#ifndef GLFW_MODULE_SCALE
#define GLFW_MODULE_SCALE 1

typedef struct {
  double x, y;
} GLFWscale;

extern thread_local JSClassID glfw_scale_class_id;
extern thread_local JSValue glfw_scale_proto, glfw_scale_class;

int glfw_scale_init(JSContext*, JSModuleDef*);
JSValue glfw_scale_wrap(JSContext*, GLFWscale*);
int glfw_scale_export(JSContext*, JSModuleDef*);

#endif
