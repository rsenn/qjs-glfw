#ifndef GLFW_MODULE_VIDEO_MODE
#define GLFW_MODULE_VIDEO_MODE 1

extern thread_local JSClassID glfw_video_mode_class_id;
extern thread_local JSValue glfw_video_mode_proto, glfw_video_mode_class;

int     glfw_video_mode_init(JSContext*, JSModuleDef*);
JSValue glfw_video_mode_wrap(JSContext*, const GLFWvidmode*);
int     glfw_video_mode_export(JSContext*, JSModuleDef*);

#endif
