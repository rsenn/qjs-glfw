#ifndef GLFW_MODULE_WINDOW
#define GLFW_MODULE_WINDOW 1

extern thread_local JSClassID glfw_window_class_id;

static inline GLFWwindow*
glfw_window_data2(JSContext* ctx, JSValueConst value) {
  return JS_GetOpaque2(ctx, value, glfw_window_class_id);
}

int glfw_window_init(JSContext* ctx, JSModuleDef* m);
int glfw_window_export(JSContext* ctx, JSModuleDef* m);

JSValue glfw_window_wrap(JSContext* ctx, GLFWwindow* window);
 
#endif
