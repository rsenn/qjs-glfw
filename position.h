#ifndef GLFW_MODULE_POSITION
#define GLFW_MODULE_POSITION 1

typedef struct {
  int x, y;
} GLFWposition;

extern JSClassID glfw_position_class_id;
JSValue glfw_position_new_instance(JSContext* ctx, GLFWposition* position);
int glfw_position_init(JSContext* ctx, JSModuleDef* m);
int glfw_position_export(JSContext* ctx, JSModuleDef* m);

#endif
