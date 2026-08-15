#ifndef QJS_GLFW_GAMMA_RAMP_H
#define QJS_GLFW_GAMMA_RAMP_H 1

extern JSClassID glfw_gamma_ramp_class_id;
extern JSValue glfw_gamma_ramp_proto, glfw_gamma_ramp_class;

int glfw_gamma_ramp_init(JSContext*, JSModuleDef*);
JSValue glfw_gamma_ramp_wrap(JSContext*, const GLFWgammaramp*);
int glfw_gamma_ramp_export(JSContext*, JSModuleDef*);

#endif
