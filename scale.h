#ifndef GLFW_MODULE_SCALE
#define GLFW_MODULE_SCALE 1

typedef struct {
  double x, y;
} GLFWscale;

extern thread_local JSClassID glfw_scale_class_id;
JSValue glfw_scale_new_instance(JSContext* ctx, GLFWscale* scale);
int glfw_scale_init(JSContext* ctx, JSModuleDef* m);
int glfw_scale_export(JSContext* ctx, JSModuleDef* m);

#endif
