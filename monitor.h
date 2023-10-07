#ifndef GLFW_MODULE_MONITOR
#define GLFW_MODULE_MONITOR 1

extern thread_local JSClassID glfw_monitor_class_id;
extern thread_local JSValue glfw_monitor_proto, glfw_monitor_class;

int glfw_monitor_init(JSContext*, JSModuleDef*);
JSValue glfw_monitor_wrap(JSContext*, GLFWmonitor*);
int glfw_monitor_export(JSContext*, JSModuleDef*);

#endif
