#ifndef GLFW_MODULE_WINDOW
#define GLFW_MODULE_WINDOW 1

extern thread_local JSClassID glfw_window_class_id;
extern thread_local JSValue glfw_window_proto, glfw_window_class;

static inline GLFWwindow*
glfw_window_data2(JSContext* ctx, JSValueConst value) {
  return JS_GetOpaque2(ctx, value, glfw_window_class_id);
}

JSValue glfw_window_wrap(JSContext*, GLFWwindow*);
int     glfw_window_init(JSContext*, JSModuleDef*);
int     glfw_window_export(JSContext*, JSModuleDef*);

 
#endif
