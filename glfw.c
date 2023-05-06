#ifdef USE_GL3W
#include <GL/glcorearb.h>
#include <GL/gl3w.h>
#endif

#include "glfw.h"
#include "position.h"
#include "size.h"
#include "window.h"
#include "monitor.h"
#include "workarea.h"
#include "gamma_ramp.h"
#include "video_mode.h"
#include "scale.h"

//#include "gl3w/src/gl3w.c"
//

#ifdef HAVE_GLFW_GET_ERROR
JSValue
glfw_throw(JSContext* ctx) {
  const char* message;
  if(glfwGetError(&message) != GLFW_NO_ERROR) {
    JSValue error = JS_NewString(ctx, message);
    JS_Throw(ctx, error);
  }
  return JS_EXCEPTION;
}
#endif

#ifdef USE_GL3W
JSValue
gl3w_getprocaddress(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  const char* str;
  void* addr;
  char buf[64];
  str = JS_ToCString(ctx, argv[0]);

  addr = gl3wGetProcAddress(str);
  // printf("gl3wGetProcAddress(\"%s\") = %p\n",str, addr);

  JS_FreeCString(ctx, str);

  snprintf(buf, sizeof(buf), "%p", addr);

  return JS_NewString(ctx, buf);
}
#endif

JSValue
glfw_poll_events(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  glfwPollEvents();
  return JS_UNDEFINED;
}

JSValue
glfw_wait_events(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  if(JS_IsNumber(argv[0])) {
    double timeout;
    if(JS_ToFloat64(ctx, &timeout, argv[0]))
      return JS_EXCEPTION;

    glfwWaitEventsTimeout(timeout);
  } else {
    glfwWaitEvents();
  }

  return JS_UNDEFINED;
}

JSValue
glfw_post_empty_event(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  if(JS_IsNumber(argv[0])) {
    double timeout;
    if(JS_ToFloat64(ctx, &timeout, argv[0]))
      return JS_EXCEPTION;

    glfwWaitEventsTimeout(timeout);
  } else {
    glfwWaitEvents();
  }

  return JS_UNDEFINED;
}

// Context
JSValue
glfw_context_get_current(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfwGetCurrentContext();
  if(!window)
    return JS_EXCEPTION;
  // TODO: window is not owned so finalizer should not destroy it
  return glfw_window_new_instance(ctx, window);
}
JSValue
glfw_context_set_current(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, value, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;
  glfwMakeContextCurrent(window);
  return JS_UNDEFINED;
}

JSValue
glfw_context_swap_interval(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int interval;
  if(JS_ToInt32(ctx, &interval, argv[0]))
    return JS_EXCEPTION;

  glfwSwapInterval(interval);

  return JS_UNDEFINED;
}

static const JSCFunctionListEntry glfw_context_props[] = {
    JS_CGETSET_DEF("current", glfw_context_get_current, glfw_context_set_current),
    JS_CFUNC_DEF("swapInterval", 2, glfw_context_swap_interval),
};

// Version
JSValue
glfw_version_to_string(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  return JS_NewString(ctx, glfwGetVersionString());
}

#define CONSTANTS(V) \
  V(FOCUSED) \
  V(ICONIFIED) \
  V(RESIZABLE) \
  V(VISIBLE) \
  V(DECORATED) \
  V(AUTO_ICONIFY) \
  V(FLOATING) \
  V(MAXIMIZED) \
  V(RED_BITS) \
  V(GREEN_BITS) \
  V(BLUE_BITS) \
  V(ALPHA_BITS) \
  V(DEPTH_BITS) \
  V(STENCIL_BITS) \
  V(ACCUM_RED_BITS) \
  V(ACCUM_GREEN_BITS) \
  V(ACCUM_BLUE_BITS) \
  V(ACCUM_ALPHA_BITS) \
  V(AUX_BUFFERS) \
  V(STEREO) \
  V(SAMPLES) \
  V(SRGB_CAPABLE) \
  V(REFRESH_RATE) \
  V(DOUBLEBUFFER) \
  V(CLIENT_API) \
  V(CONTEXT_VERSION_MAJOR) \
  V(CONTEXT_VERSION_MINOR) \
  V(CONTEXT_REVISION) \
  V(CONTEXT_ROBUSTNESS) \
  V(OPENGL_FORWARD_COMPAT) \
  V(OPENGL_DEBUG_CONTEXT) \
  V(OPENGL_PROFILE) \
  V(CONTEXT_RELEASE_BEHAVIOR) \
  V(CONTEXT_NO_ERROR) \
  V(CONTEXT_CREATION_API) \
  V(OPENGL_CORE_PROFILE) \
  V(VERSION_MAJOR) \
  V(VERSION_MINOR) \
  V(VERSION_REVISION)

#define CONSTANTS2(V) \
  V(CENTER_CURSOR) \
  V(TRANSPARENT_FRAMEBUFFER) \
  V(HOVERED) \
  V(FOCUS_ON_SHOW) \
  V(SCALE_TO_MONITOR) \
  V(COCOA_RETINA_FRAMEBUFFER) \
  V(COCOA_FRAME_NAME) \
  V(COCOA_GRAPHICS_SWITCHING) \
  V(X11_CLASS_NAME) \
  V(X11_INSTANCE_NAME) \
  V(JOYSTICK_HAT_BUTTONS) \
  V(COCOA_CHDIR_RESOURCES) \
  V(COCOA_MENUBAR)

#define DEFINE_CONSTANT(Name) JS_PROP_INT32_DEF(#Name, GLFW_##Name, 0),

const JSCFunctionListEntry glfw_exports[] = {
    JS_CFUNC_DEF("poll", 2, glfw_poll_events),
    JS_CFUNC_DEF("wait", 2, glfw_wait_events),
#ifdef USE_GL3W
    JS_CFUNC_DEF("getProcAddress", 1, gl3w_getprocaddress),
#endif
    JS_CFUNC_DEF("postEmptyEvent", 2, glfw_post_empty_event),
    JS_OBJECT_DEF("context", glfw_context_props, countof(glfw_context_props), JS_PROP_CONFIGURABLE),
    CONSTANTS(DEFINE_CONSTANT)
    // CONSTANTS2(DEFINE_CONSTANT),
};

#undef CONSTANTS
#undef DEFINE_CONSTANT

// initialization
int
glfw_init(JSContext* ctx, JSModuleDef* m) {
  JS_SetModuleExportList(ctx, m, glfw_exports, countof(glfw_exports));

  glfw_position_init(ctx, m);
  glfw_size_init(ctx, m);
  glfw_gamma_ramp_init(ctx, m);
  glfw_monitor_init(ctx, m);
  glfw_scale_init(ctx, m);
  glfw_video_mode_init(ctx, m);
  glfw_window_init(ctx, m);
  glfw_workarea_init(ctx, m);

  // TODO: lazy-load version info with a getter?
  int major, minor, revision;
  glfwGetVersion(&major, &minor, &revision);
  JSValue version = JS_NewObject(ctx);
  JS_SetPropertyStr(ctx, version, "major", JS_NewInt32(ctx, major));
  JS_SetPropertyStr(ctx, version, "minor", JS_NewInt32(ctx, minor));
  JS_SetPropertyStr(ctx, version, "revision", JS_NewInt32(ctx, revision));
  JS_SetPropertyStr(ctx, version, "toString", JS_NewCFunction(ctx, glfw_version_to_string, "toString", 0));
  JS_SetModuleExport(ctx, m, "version", version);

  return 0;
}

int
glfw_export(JSContext* ctx, JSModuleDef* m) {
  JS_AddModuleExportList(ctx, m, glfw_exports, countof(glfw_exports));

  glfw_position_export(ctx, m);
  glfw_size_export(ctx, m);
  glfw_gamma_ramp_export(ctx, m);
  glfw_monitor_export(ctx, m);
  glfw_scale_export(ctx, m);
  glfw_video_mode_export(ctx, m);
  glfw_window_export(ctx, m);
  glfw_workarea_export(ctx, m);

  JS_AddModuleExport(ctx, m, "version");

  return 0;
}

JSModuleDef*
js_init_module(JSContext* ctx, const char* module_name) {
  JSModuleDef* m = JS_NewCModule(ctx, module_name, glfw_init);
  if(!m)
    return NULL;

  glfw_export(ctx, m);

  {
    static BOOL initialized;

    if(!initialized) {
      // TODO: Is it possible to check errors for init and throw in module import?
      glfwInit();

#ifdef USE_GL3W
      gl3wInit();
#endif
      // atexit(glfwTerminate);

/*      int result = gl3wInit();
      printf("gl3wInit() = %d\n", result);*/

           /*glewExperimental = GL_TRUE;
      if(glewInit() != GLEW_OK) {
        printf("Could not init glew.\n");
        return 0;
      }

      // GLEW generates GL error because it calls glGetString(GL_EXTENSIONS), we'll consume it here.
      glGetError();*/

      initialized = TRUE;
    }
  }

  return m;
}
