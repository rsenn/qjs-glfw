#ifndef GLFW_MODULE_IMAGE
#define GLFW_MODULE_IMAGE 1

extern thread_local JSClassID glfw_image_class_id;
extern thread_local JSValue glfw_image_proto, glfw_image_class;

int glfw_image_init(JSContext*, JSModuleDef*);
JSValue glfw_image_wrap(JSContext*, const GLFWimage*);
int glfw_image_export(JSContext*, JSModuleDef*);

#endif
