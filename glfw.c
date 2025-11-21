#ifdef USE_GL3W
#include <GL/glcorearb.h>
#include <GL/gl3w.h>
#endif
#include <assert.h>
#include <string.h>

#include "glfw.h"
#include "window.h"
#include "monitor.h"
#include "gamma_ramp.h"
#include "image.h"
#include "video_mode.h"
#include "position.h"

//#include "gl3w/src/gl3w.c"
//
BOOL glfw_initialized = FALSE;

BOOL
glfw_initialize(JSContext* ctx) {
  assert(!glfw_initialized);

  // TODO: Is it possible to check errors for init and throw in module import?
  if(glfwInit() == GLFW_TRUE) {

#ifdef USE_GL3W
    gl3wInit();
#endif

    glfw_initialized = TRUE;
  }

  return glfw_initialized;
}

#ifdef HAVE_GLFW_GET_ERROR
JSValue
glfw_throw(JSContext* ctx, const char* func) {
  const char* message;

  if(glfwGetError(&message) != GLFW_NO_ERROR) {
    JSValue error = JS_NewError(ctx);

    char* s;

    if((s = js_malloc(ctx, strlen(message) + strlen(func) + 4))) {
      strcpy(s, "In ");
      strcat(s, func);
      strcat(s, "(): ");
      strcat(s, message);

      JS_SetPropertyStr(ctx, error, "message", JS_NewString(ctx, s));
      js_free(ctx, s);
    }
    JS_SetPropertyStr(ctx, error, "function", JS_NewString(ctx, func));

    JS_Throw(ctx, error);
  }

  return JS_EXCEPTION;
}
#endif

static JSValue
glfw_getprocaddress(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  const char* str;
  void* addr;
  char buf[64];
  str = JS_ToCString(ctx, argv[0]);

#ifdef USE_GL3W
  addr = gl3wGetProcAddress(str);
#else
  addr = glfwGetProcAddress(str);
#endif

  JS_FreeCString(ctx, str);

  snprintf(buf, sizeof(buf), "%p", addr);

  return JS_NewString(ctx, buf);
}

enum {
  TIME_GET,
  TIME_SET,
  TIMER_VALUE_GET,
  TIMER_FREQUENCY_GET,
};

static JSValue
glfw_time(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  switch(magic) {
    case TIME_GET: {
      ret = JS_NewFloat64(ctx, glfwGetTime());
      break;
    }

    case TIME_SET: {
      double t = 0;
      JS_ToFloat64(ctx, &t, argv[0]);
      glfwSetTime(t);
      break;
    }

    case TIMER_VALUE_GET: {
      ret = JS_NewInt64(ctx, glfwGetTimerValue());
      break;
    }

    case TIMER_FREQUENCY_GET: {
      ret = JS_NewInt64(ctx, glfwGetTimerFrequency());
      break;
    }
  }

  return ret;
}

enum {
  GET_PLATFORM,
  SUPPORTED_PLATFORM,
  KEY_NAME,
  KEY_SCANCODE,
  TERMINATE,
  POST_EMPTY_EVENT,
  EXTENSION_SUPPORTED,
};

static JSValue
glfw_other(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  JSValue ret = JS_UNDEFINED;

  switch(magic) {
#ifdef HAVE_GLFW_GET_PLATFORM
    case GET_PLATFORM: {
      ret = JS_NewInt32(ctx, glfwGetPlatform());
      break;
    }
#endif

#ifdef HAVE_GLFW_PLATFORM_SUPPORTED
    case SUPPORTED_PLATFORM: {
      int32_t p = -1;
      JS_ToInt32(ctx, &p, argv[0]);

      ret = JS_NewInt32(ctx, glfwPlatformSupported(p));
      break;
    }
#endif

    case KEY_NAME: {
      int32_t key = -1, scancode = -1;
      const char* name;

      JS_ToInt32(ctx, &key, argv[0]);

      if(argc > 1)
        JS_ToInt32(ctx, &scancode, argv[1]);
      else
        scancode = glfwGetKeyScancode(key);

      ret = (name = glfwGetKeyName(key, scancode)) ? JS_NewString(ctx, name) : JS_NULL;
      break;
    }

    case KEY_SCANCODE: {
      int32_t key = -1;

      JS_ToInt32(ctx, &key, argv[0]);

      ret = JS_NewInt32(ctx, glfwGetKeyScancode(key));
      break;
    }

    case TERMINATE: {
      glfwTerminate();
      break;
    }

    case POST_EMPTY_EVENT: {
      glfwPostEmptyEvent();
      break;
    }

    case EXTENSION_SUPPORTED: {
      const char* str;

      if((str = JS_ToCString(ctx, argv[0]))) {
        ret = JS_NewBool(ctx, glfwExtensionSupported(str) == GLFW_TRUE);
        JS_FreeCString(ctx, str);
      }
      break;
    }
  }

  return ret;
}

static JSValue
glfw_cursor_create(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWimage* image;
  GLFWposition_i position;
  int32_t x, y;

  if(!(image = JS_GetOpaque(argv[0], glfw_image_class_id)))
    return JS_ThrowTypeError(ctx, "argument 1 must be a glfw.Image");

  if(JS_IsObject(argv[1])) {
    glfw_position_i_read(ctx, &position, argv[1]);
    x = position.x;
    y = position.y;
  } else {
    if(JS_ToInt32(ctx, &x, argv[1]))
      return JS_ThrowTypeError(ctx, "argument 2 (hot-x) must be a number");

    if(JS_ToInt32(ctx, &y, argv[2]))
      return JS_ThrowTypeError(ctx, "argument 3 (hot-y) must be a number");
  }

  return js_newptr(ctx, glfwCreateCursor(image, x, y));
}

static JSValue
glfw_cursor_create_std(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  int32_t shape;

  if(JS_ToInt32(ctx, &shape, argv[0]))
    return JS_ThrowTypeError(ctx, "argument 1 (shape) must be a number");

  return js_newptr(ctx, glfwCreateStandardCursor(shape));
}

static JSValue
glfw_cursor_destroy(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWcursor* cursor;

  if(!(cursor = js_getptr(ctx, argv[0])))
    return JS_ThrowTypeError(ctx, "argument 1 must be a glfw.Cursor");

  glfwDestroyCursor(cursor);

  return JS_UNDEFINED;
}

static JSValue
glfw_poll_events(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  glfwPollEvents();
  return JS_UNDEFINED;
}

static JSValue
glfw_wait_events(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
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
static JSValue
glfw_context_get_current(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfwGetCurrentContext();

  if(!(window = glfwGetCurrentContext()))
    return JS_ThrowInternalError(ctx, "No GLFWwindow (glfwGetCurrentContext() returned NULL)");

  // TODO: window is not owned so finalizer should not destroy it
  return glfw_window_wrap(ctx, window);
}

static JSValue
glfw_context_set_current(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, value, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;
  glfwMakeContextCurrent(window);
  return JS_UNDEFINED;
}

static JSValue
glfw_context_swap_interval(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  int interval;
  if(JS_ToInt32(ctx, &interval, argv[0]))
    return JS_EXCEPTION;

  glfwSwapInterval(interval);

  return JS_UNDEFINED;
}

static const JSCFunctionListEntry glfw_context_props[] = {
    // JS_CGETSET_DEF("__proto__", glfw_context_get_proto, 0),
    JS_CGETSET_DEF("current", glfw_context_get_current, glfw_context_set_current),
    JS_CFUNC_DEF("swapInterval", 2, glfw_context_swap_interval),
};

// Version
static JSValue
glfw_version_to_string(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  return JS_NewString(ctx, glfwGetVersionString());
}

#define GLFW_PLATFORM_CONST X11

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

static const JSCFunctionListEntry glfw_exports[] = {
    JS_CFUNC_DEF("poll", 0, glfw_poll_events),
    JS_CFUNC_DEF("wait", 1, glfw_wait_events),
    JS_CFUNC_DEF("getProcAddress", 1, glfw_getprocaddress),
    JS_CFUNC_MAGIC_DEF("getTime", 0, glfw_time, TIME_GET),
    JS_CFUNC_MAGIC_DEF("setTime", 1, glfw_time, TIME_SET),
    JS_CFUNC_MAGIC_DEF("getTimerValue", 0, glfw_time, TIMER_VALUE_GET),
    JS_CFUNC_MAGIC_DEF("getTimerFrequency", 0, glfw_time, TIMER_FREQUENCY_GET),
#ifdef HAVE_GLFW_GET_PLATFORM
    JS_CFUNC_MAGIC_DEF("getPlatform", 0, glfw_other, GET_PLATFORM),
#endif
#ifdef HAVE_GLFW_PLATFORM_SUPPORTED
    JS_CFUNC_MAGIC_DEF("platformSupported", 1, glfw_other, SUPPORTED_PLATFORM),
#endif
    JS_CFUNC_MAGIC_DEF("getKeyName", 1, glfw_other, KEY_NAME),
    JS_CFUNC_MAGIC_DEF("getKeyScancode", 1, glfw_other, KEY_SCANCODE),
    JS_CFUNC_MAGIC_DEF("terminate", 0, glfw_other, TERMINATE),
    JS_CFUNC_MAGIC_DEF("postEmptyEvent", 0, glfw_other, POST_EMPTY_EVENT),
    JS_CFUNC_MAGIC_DEF("extensionSupported", 1, glfw_other, EXTENSION_SUPPORTED),
    JS_CFUNC_DEF("createCursor", 2, glfw_cursor_create),
    JS_CFUNC_DEF("createStandardCursor", 1, glfw_cursor_create_std),
    JS_CFUNC_DEF("destroyCursor", 1, glfw_cursor_destroy),
    JS_OBJECT_DEF("context", glfw_context_props, countof(glfw_context_props), JS_PROP_CONFIGURABLE),
#ifdef GLFW_PLATFORM_WAYLAND
    JS_PROP_INT32_DEF("PLATFORM_WAYLAND", GLFW_PLATFORM_WAYLAND, 0),
#endif
#ifdef GLFW_PLATFORM_COCOA
    JS_PROP_INT32_DEF("PLATFORM_COCOA", GLFW_PLATFORM_COCOA, 0),
#endif
#ifdef GLFW_PLATFORM_WIN32
    JS_PROP_INT32_DEF("PLATFORM_WIN32", GLFW_PLATFORM_WIN32, 0),
#endif
#ifdef GLFW_PLATFORM_X11
    JS_PROP_INT32_DEF("PLATFORM_X11", GLFW_PLATFORM_X11, 0),
#endif
#ifdef GLFW_PLATFORM_NULL
    JS_PROP_INT32_DEF("PLATFORM_NULL", GLFW_PLATFORM_NULL, 0),
#endif
#ifdef GLFW_ANY_PLATFORM
    JS_PROP_INT32_DEF("ANY_PLATFORM", GLFW_ANY_PLATFORM, 0),
#endif
    CONSTANTS(DEFINE_CONSTANT)

        DEFINE_CONSTANT(KEY_UNKNOWN) DEFINE_CONSTANT(KEY_SPACE) DEFINE_CONSTANT(KEY_APOSTROPHE) DEFINE_CONSTANT(
            KEY_COMMA) DEFINE_CONSTANT(KEY_MINUS) DEFINE_CONSTANT(KEY_PERIOD) DEFINE_CONSTANT(KEY_SLASH) DEFINE_CONSTANT(KEY_0)
            DEFINE_CONSTANT(KEY_1) DEFINE_CONSTANT(KEY_2) DEFINE_CONSTANT(KEY_3) DEFINE_CONSTANT(KEY_4) DEFINE_CONSTANT(
                KEY_5) DEFINE_CONSTANT(KEY_6) DEFINE_CONSTANT(KEY_7) DEFINE_CONSTANT(KEY_8) DEFINE_CONSTANT(KEY_9)
                DEFINE_CONSTANT(KEY_SEMICOLON) DEFINE_CONSTANT(KEY_EQUAL) DEFINE_CONSTANT(KEY_A) DEFINE_CONSTANT(
                    KEY_B) DEFINE_CONSTANT(KEY_C) DEFINE_CONSTANT(KEY_D) DEFINE_CONSTANT(KEY_E) DEFINE_CONSTANT(KEY_F)
                    DEFINE_CONSTANT(KEY_G) DEFINE_CONSTANT(KEY_H) DEFINE_CONSTANT(KEY_I) DEFINE_CONSTANT(
                        KEY_J) DEFINE_CONSTANT(KEY_K) DEFINE_CONSTANT(KEY_L) DEFINE_CONSTANT(KEY_M) DEFINE_CONSTANT(KEY_N)
                        DEFINE_CONSTANT(KEY_O) DEFINE_CONSTANT(KEY_P) DEFINE_CONSTANT(KEY_Q) DEFINE_CONSTANT(KEY_R) DEFINE_CONSTANT(
                            KEY_S) DEFINE_CONSTANT(KEY_T) DEFINE_CONSTANT(KEY_U) DEFINE_CONSTANT(KEY_V) DEFINE_CONSTANT(KEY_W)
                            DEFINE_CONSTANT(KEY_X) DEFINE_CONSTANT(KEY_Y) DEFINE_CONSTANT(KEY_Z) DEFINE_CONSTANT(
                                KEY_LEFT_BRACKET) DEFINE_CONSTANT(KEY_BACKSLASH) DEFINE_CONSTANT(KEY_RIGHT_BRACKET)
                                DEFINE_CONSTANT(KEY_GRAVE_ACCENT) DEFINE_CONSTANT(KEY_WORLD_1) DEFINE_CONSTANT(
                                    KEY_WORLD_2) DEFINE_CONSTANT(KEY_ESCAPE) DEFINE_CONSTANT(KEY_ENTER) DEFINE_CONSTANT(KEY_TAB)
                                    DEFINE_CONSTANT(KEY_BACKSPACE) DEFINE_CONSTANT(KEY_INSERT) DEFINE_CONSTANT(KEY_DELETE) DEFINE_CONSTANT(
                                        KEY_RIGHT) DEFINE_CONSTANT(KEY_LEFT) DEFINE_CONSTANT(KEY_DOWN) DEFINE_CONSTANT(KEY_UP) DEFINE_CONSTANT(KEY_PAGE_UP)
                                        DEFINE_CONSTANT(KEY_PAGE_DOWN) DEFINE_CONSTANT(KEY_HOME) DEFINE_CONSTANT(KEY_END) DEFINE_CONSTANT(
                                            KEY_CAPS_LOCK) DEFINE_CONSTANT(KEY_SCROLL_LOCK) DEFINE_CONSTANT(KEY_NUM_LOCK)
                                            DEFINE_CONSTANT(KEY_PRINT_SCREEN) DEFINE_CONSTANT(
                                                KEY_PAUSE) DEFINE_CONSTANT(KEY_F1) DEFINE_CONSTANT(KEY_F2) DEFINE_CONSTANT(KEY_F3)
                                                DEFINE_CONSTANT(
                                                    KEY_F4) DEFINE_CONSTANT(KEY_F5)
                                                    DEFINE_CONSTANT(
                                                        KEY_F6) DEFINE_CONSTANT(KEY_F7)
                                                        DEFINE_CONSTANT(
                                                            KEY_F8) DEFINE_CONSTANT(KEY_F9)
                                                            DEFINE_CONSTANT(KEY_F10) DEFINE_CONSTANT(KEY_F11) DEFINE_CONSTANT(
                                                                KEY_F12) DEFINE_CONSTANT(KEY_F13) DEFINE_CONSTANT(KEY_F14)
                                                                DEFINE_CONSTANT(KEY_F15) DEFINE_CONSTANT(KEY_F16) DEFINE_CONSTANT(
                                                                    KEY_F17) DEFINE_CONSTANT(KEY_F18) DEFINE_CONSTANT(KEY_F19)
                                                                    DEFINE_CONSTANT(KEY_F20) DEFINE_CONSTANT(KEY_F21) DEFINE_CONSTANT(
                                                                        KEY_F22) DEFINE_CONSTANT(KEY_F23) DEFINE_CONSTANT(KEY_F24)
                                                                        DEFINE_CONSTANT(KEY_F25) DEFINE_CONSTANT(KEY_KP_0) DEFINE_CONSTANT(
                                                                            KEY_KP_1) DEFINE_CONSTANT(KEY_KP_2)
                                                                            DEFINE_CONSTANT(KEY_KP_3) DEFINE_CONSTANT(
                                                                                KEY_KP_4) DEFINE_CONSTANT(KEY_KP_5)
                                                                                DEFINE_CONSTANT(KEY_KP_6) DEFINE_CONSTANT(
                                                                                    KEY_KP_7) DEFINE_CONSTANT(KEY_KP_8)
                                                                                    DEFINE_CONSTANT(KEY_KP_9) DEFINE_CONSTANT(
                                                                                        KEY_KP_DECIMAL) DEFINE_CONSTANT(KEY_KP_DIVIDE)
                                                                                        DEFINE_CONSTANT(KEY_KP_MULTIPLY) DEFINE_CONSTANT(
                                                                                            KEY_KP_SUBTRACT) DEFINE_CONSTANT(KEY_KP_ADD)
                                                                                            DEFINE_CONSTANT(KEY_KP_ENTER) DEFINE_CONSTANT(
                                                                                                KEY_KP_EQUAL) DEFINE_CONSTANT(KEY_LEFT_SHIFT)
                                                                                                DEFINE_CONSTANT(KEY_LEFT_CONTROL) DEFINE_CONSTANT(
                                                                                                    KEY_LEFT_ALT) DEFINE_CONSTANT(KEY_LEFT_SUPER)
                                                                                                    DEFINE_CONSTANT(
                                                                                                        KEY_RIGHT_SHIFT)
                                                                                                        DEFINE_CONSTANT(
                                                                                                            KEY_RIGHT_CONTROL)
                                                                                                            DEFINE_CONSTANT(
                                                                                                                KEY_RIGHT_ALT)
                                                                                                                DEFINE_CONSTANT(
                                                                                                                    KEY_RIGHT_SUPER)
                                                                                                                    DEFINE_CONSTANT(
                                                                                                                        KEY_MENU)
                                                                                                                        DEFINE_CONSTANT(
                                                                                                                            KEY_LAST)

    // CONSTANTS2(DEFINE_CONSTANT),
};

#undef CONSTANTS
#undef DEFINE_CONSTANT

// initialization
int
glfw_init(JSContext* ctx, JSModuleDef* m) {

  if(!glfw_initialized)
    assert(glfw_initialize(ctx));

  JS_SetModuleExportList(ctx, m, glfw_exports, countof(glfw_exports));

  glfw_position_init(ctx, m);
  glfw_size_init(ctx, m);
  glfw_gamma_ramp_init(ctx, m);
  glfw_image_init(ctx, m);
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

  JS_SetModuleExport(ctx, m, "rawMouseMotionSupported", JS_NewBool(ctx, glfwRawMouseMotionSupported() == GLFW_TRUE));

  return 0;
}

int
glfw_export(JSContext* ctx, JSModuleDef* m) {
  JS_AddModuleExportList(ctx, m, glfw_exports, countof(glfw_exports));

  glfw_position_export(ctx, m);
  glfw_size_export(ctx, m);
  glfw_gamma_ramp_export(ctx, m);
  glfw_image_export(ctx, m);
  glfw_monitor_export(ctx, m);
  glfw_scale_export(ctx, m);
  glfw_video_mode_export(ctx, m);
  glfw_window_export(ctx, m);
  glfw_workarea_export(ctx, m);

  JS_AddModuleExport(ctx, m, "version");
  JS_AddModuleExport(ctx, m, "rawMouseMotionSupported");

  return 0;
}

JSModuleDef*
js_init_module(JSContext* ctx, const char* module_name) {
  JSModuleDef* m = JS_NewCModule(ctx, module_name, glfw_init);
  if(!m)
    return NULL;

  glfw_export(ctx, m);

  return m;
}
