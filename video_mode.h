#ifndef GLFW_MODULE_VIDEO_MODE
#define GLFW_MODULE_VIDEO_MODE 1

extern thread_local JSClassID glfw_video_mode_class_id;
JSValue glfw_video_mode_wrap(JSContext* ctx, const GLFWvidmode* mode);
int glfw_video_mode_init(JSContext* ctx, JSModuleDef* m);
int glfw_video_mode_export(JSContext* ctx, JSModuleDef* m);

#endif
