#ifndef GLFW_MODULE_SIZE
#define GLFW_MODULE_SIZE 1

typedef struct {
  int width, height;
} GLFWsize;

extern thread_local JSClassID glfw_size_class_id;
extern thread_local JSValue glfw_size_proto, glfw_size_class;

int glfw_size_init(JSContext*, JSModuleDef*);
JSValue glfw_size_wrap(JSContext*, GLFWsize*);
int glfw_size_export(JSContext*, JSModuleDef*);

#endif
