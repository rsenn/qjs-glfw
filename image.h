#ifndef GLFW_MODULE_IMAGE
#define GLFW_MODULE_IMAGE 1

extern JSClassID glfw_image_class_id;
extern JSValue glfw_image_proto, glfw_image_class;

int glfw_image_init(JSContext*, JSModuleDef*);
int glfw_image_export(JSContext*, JSModuleDef*);

#endif
