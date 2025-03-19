#ifndef GLFW_MODULE_MONITOR
#define GLFW_MODULE_MONITOR 1

extern JSClassID glfw_monitor_class_id;
extern JSValue glfw_monitor_proto, glfw_monitor_class;

int glfw_monitor_init(JSContext*, JSModuleDef*);
JSValue glfw_monitor_wrap(JSContext*, GLFWmonitor*);
int glfw_monitor_export(JSContext*, JSModuleDef*);

#endif
