#ifndef GLFW_MODULE_VIDEO_MODE
#define GLFW_MODULE_VIDEO_MODE 1

extern JSClassID glfw_video_mode_class_id;
extern JSValue glfw_video_mode_proto, glfw_video_mode_class;

int glfw_video_mode_init(JSContext*, JSModuleDef*);
JSValue glfw_video_mode_wrap(JSContext*, GLFWvidmode);
int glfw_video_mode_export(JSContext*, JSModuleDef*);

#endif
