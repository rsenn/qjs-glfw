#include "glfw.h"
#include "monitor.h"
#include "position.h"
#include "size.h"

#include "window.h"

JSClassID glfw_window_class_id = 0;

enum CallbackID {
  CALLBACK_WINDOW_POS = 0,
  CALLBACK_WINDOW_SIZE,
  CALLBACK_WINDOW_CLOSE,
  CALLBACK_WINDOW_REFRESH,
  CALLBACK_WINDOW_FOCUS,
  CALLBACK_WINDOW_ICONIFY,
  CALLBACK_WINDOW_MAXIMIZE,
  CALLBACK_FRAMEBUFFER_SIZE,
  CALLBACK_WINDOW_CONTENT_SCALE,
  CALLBACK_MOUSE_BUTTON,
  CALLBACK_CURSOR_POS,
  CALLBACK_CURSOR_ENTER,
  CALLBACK_SCROLL,
  CALLBACK_KEY,
  CALLBACK_CHAR,
  CALLBACK_CHAR_MODS,
  CALLBACK_DROP,
  _CALLBACK_LAST
};

typedef struct WindowContext {
  union {
    struct {
      JSValue window_pos_handler, window_size_handler, window_close_handler, window_refresh_handler, window_focus_handler,
          window_iconify_handler, window_maximize_handler, framebuffer_size_handler, window_content_scale_handler,
          mouse_button_handler, cursor_pos_handler, cursor_enter_handler, scroll_handler, key_handler, char_handler,
          char_mods_handler, drop_handler;
    };
    JSValue list[_CALLBACK_LAST];
  } handlers;
  JSContext* ctx;
} WindowContext;

static void
glfw_handle_charfun(GLFWwindow* w, unsigned int c) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_charmodsfun(GLFWwindow* w, unsigned int c, int mods) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_cursorenterfun(GLFWwindow* w, int cur) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_cursorposfun(GLFWwindow* w, double x, double y) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_dropfun(GLFWwindow* w, int argc, const char* argv[]) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

// static void glfw_handle_errorfun(int,const char*) {}
static void
glfw_handle_framebuffersizefun(GLFWwindow* w, int width, int height) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

// static void glfw_handle_joystickfun(int,int) {}
static void
glfw_handle_keyfun(GLFWwindow* w, int key, int scancode, int action, int mods) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

/*static void
glfw_handle_monitorfun(GLFWmonitor* m, int event) {
  WindowContext* wc = glfwGetMonitorUserPointer(w);
}
*/
static void
glfw_handle_mousebuttonfun(GLFWwindow* w, int button, int action, int mods) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_scrollfun(GLFWwindow* w, double xoffset, double yoffset) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowclosefun(GLFWwindow* w) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowcontentscalefun(GLFWwindow* w, float sx, float sy) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowfocusfun(GLFWwindow* w, int focused) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowiconifyfun(GLFWwindow* w, int iconified) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowmaximizefun(GLFWwindow* w, int iconified) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowposfun(GLFWwindow* w, int x, int y) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowrefreshfun(GLFWwindow* w) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

static void
glfw_handle_windowsizefun(GLFWwindow* w, int width, int height) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
}

// Constructor/Destructor
JSValue
glfw_window_ctor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv) {
  int width, height;
  const char* title;
  GLFWmonitor* monitor = NULL;
  GLFWwindow* share = NULL;

  if(JS_ToInt32(ctx, &width, argv[0]))
    return JS_EXCEPTION;

  if(JS_ToInt32(ctx, &height, argv[1]))
    return JS_EXCEPTION;

  title = JS_ToCString(ctx, argv[2]);
  if(!title)
    return JS_EXCEPTION;

  // if (JS_IsObject(argv[3])) {
  //   monitor = JS_GetOpaque2(ctx, argv[3], glfw_monitor_class_id);
  // }

  // if (JS_IsObject(argv[4])) {
  //   share = JS_GetOpaque2(ctx, argv[4], glfw_window_class_id);
  // }

  return glfw_window_create_window(ctx, width, height, title, monitor, share);
}

// Instance Methods
JSValue
glfw_window_make_context_current(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;
  glfwMakeContextCurrent(window);
  return JS_UNDEFINED;
}
JSValue
glfw_window_swap_buffers(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;
  glfwSwapBuffers(window);
  return JS_UNDEFINED;
}

// Static  Methods
JSValue
glfw_window_hint(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int key;

  if(JS_ToInt32(ctx, &key, argv[0]))
    return JS_EXCEPTION;

  if(JS_IsString(argv[1])) {
    const char* value = JS_ToCString(ctx, argv[1]);
    glfwWindowHintString(key, value);
  } else if(JS_IsBool(argv[1])) {
    int value = JS_VALUE_GET_BOOL(argv[1]) == 1 ? GL_TRUE : GL_FALSE;
    glfwWindowHint(key, value);
  } else if(JS_IsNumber(argv[1])) {
    int value;
    if(JS_ToInt32(ctx, &value, argv[1]))
      return JS_EXCEPTION;

    glfwWindowHint(key, value);
  } else {
    JS_ThrowTypeError(ctx, "Value must be a number or string");
    return JS_EXCEPTION;
  }

  return JS_UNDEFINED;
}
JSValue
glfw_window_default_hints(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  glfwDefaultWindowHints();
  return JS_UNDEFINED;
}

// Properties
JSValue
glfw_window_get_should_close(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  if(glfwWindowShouldClose(window))
    return JS_TRUE;
  else
    return JS_FALSE;
}
JSValue
glfw_window_set_should_close(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;
  int shouldClose = JS_VALUE_GET_BOOL(value) == 1 ? GL_TRUE : GL_FALSE;
  glfwSetWindowShouldClose(window, shouldClose);
  return JS_UNDEFINED;
}

JSValue
glfw_window_set_title(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  if(!JS_IsString(value)) {
    JS_ThrowTypeError(ctx, "Title must be a string");
    return JS_EXCEPTION;
  }

  const char* title = JS_ToCString(ctx, value);
  glfwSetWindowTitle(window, title);
  return JS_UNDEFINED;
}

JSValue
glfw_window_set_position(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  GLFWPosition* position = JS_GetOpaque2(ctx, value, glfw_position_class_id);
  if(!position)
    return JS_EXCEPTION;

  glfwSetWindowPos(window, position->x, position->y);
  return JS_UNDEFINED;
}
JSValue
glfw_window_get_position(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  GLFWPosition* position = js_mallocz(ctx, sizeof(*position));
  glfwGetWindowPos(window, &position->x, &position->y);
  return glfw_position_new_instance(ctx, position);
}

// TODO: magic these with position setter/getter?
JSValue
glfw_window_set_size(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  GLFWSize* size = JS_GetOpaque2(ctx, value, glfw_size_class_id);
  if(!size)
    return JS_EXCEPTION;

  glfwSetWindowSize(window, size->width, size->height);
  return JS_UNDEFINED;
}
JSValue
glfw_window_get_size(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  GLFWSize* size = js_mallocz(ctx, sizeof(*size));
  glfwGetWindowSize(window, &size->width, &size->height);
  return glfw_size_new_instance(ctx, size);
}
JSValue
glfw_window_get_framebuffer_size(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  GLFWSize* size = js_mallocz(ctx, sizeof(*size));
  glfwGetFramebufferSize(window, &size->width, &size->height);
  return glfw_size_new_instance(ctx, size);
}
JSValue
glfw_window_set_opacity(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  double opacity;
  if(JS_ToFloat64(ctx, &opacity, value))
    return JS_EXCEPTION;

  glfwSetWindowOpacity(window, opacity);
  return JS_UNDEFINED;
}
JSValue
glfw_window_get_opacity(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;
  return JS_NewFloat64(ctx, glfwGetWindowOpacity(window));
}
JSValue
glfw_window_get_monitor(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  if(!window)
    return JS_EXCEPTION;

  GLFWmonitor* monitor = glfwGetWindowMonitor(window);
  if(!monitor) {
    return JS_UNDEFINED;
  }

  return glfw_monitor_new_instance(ctx, monitor);
}

JSValue
glfw_window_get_callback(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  WindowContext* wc;
  if(!window)
    return JS_EXCEPTION;

  if((wc = glfwGetWindowUserPointer(window)))
    return JS_DupValue(ctx, wc->handlers.list[magic]);

  return JS_UNDEFINED;
}

JSValue
glfw_window_set_callback(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);
  WindowContext* wc;
  if(!window)
    return JS_EXCEPTION;

  if((wc = glfwGetWindowUserPointer(window))) {
    if(!JS_IsUndefined(wc->handlers.list[magic]))
      JS_FreeValue(ctx, wc->handlers.list[magic]);

    wc->handlers.list[magic] = JS_DupValue(ctx, value);

    return JS_NewBool(ctx, JS_IsFunction(ctx, wc->handlers.list[magic]));
  }

  return JS_UNDEFINED;
}

// Generate a few simple methods with macros...because I'm lazy. :O
#define TRIGGER_FUNCTIONS(V)                                                                                                   \
  V(IconifyWindow, iconify)                                                                                                    \
  V(RestoreWindow, restore)                                                                                                    \
  V(MaximizeWindow, maximize)                                                                                                  \
  V(ShowWindow, show)                                                                                                          \
  V(HideWindow, hide)                                                                                                          \
  V(FocusWindow, focus)                                                                                                        \
  V(RequestWindowAttention, requestAttention)

#define MAKE_TRIGGER_METHOD(NativeName, JSName)                                                                                \
  JSValue glfw_window_##JSName(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {                          \
    GLFWwindow* window = JS_GetOpaque2(ctx, this_val, glfw_window_class_id);                                                   \
    glfw##NativeName(window);                                                                                                  \
    if(!window)                                                                                                                \
      return JS_EXCEPTION;                                                                                                     \
    return JS_UNDEFINED;                                                                                                       \
  }
TRIGGER_FUNCTIONS(MAKE_TRIGGER_METHOD)
#undef MAKE_TRIGGER_METHODS

// Initialization
JSClassDef glfw_window_class_def = {
    "Window",
};

#define MAKE_TRIGGER_METHOD_ENTRY(NativeName, JSName) JS_CFUNC_DEF(#JSName, 0, glfw_window_##JSName),

const JSCFunctionListEntry glfw_window_proto_funcs[] = {
    JS_CFUNC_DEF("makeContextCurrent", 0, glfw_window_make_context_current),
    JS_CFUNC_DEF("swapBuffers", 0, glfw_window_swap_buffers),
    JS_CGETSET_DEF("shouldClose", glfw_window_get_should_close, glfw_window_set_should_close),
    JS_CGETSET_DEF("title", NULL, glfw_window_set_title),
    JS_CGETSET_DEF("position", glfw_window_get_position, glfw_window_set_position),
    JS_CGETSET_DEF("size", glfw_window_get_size, glfw_window_set_size),
    JS_CGETSET_DEF("framebufferSize", glfw_window_get_framebuffer_size, NULL),
    JS_CGETSET_DEF("opacity", glfw_window_get_opacity, glfw_window_set_opacity),
    JS_CGETSET_DEF("monitor", glfw_window_get_monitor, NULL),
    JS_CGETSET_MAGIC_DEF("handleWindowPos", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_POS),
    JS_CGETSET_MAGIC_DEF("handleWindowSize", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_SIZE),
    JS_CGETSET_MAGIC_DEF("handleWindowClose", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_CLOSE),
    JS_CGETSET_MAGIC_DEF("handleWindowRefresh", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_REFRESH),
    JS_CGETSET_MAGIC_DEF("handleWindowFocus", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_FOCUS),
    JS_CGETSET_MAGIC_DEF("handleWindowIconify", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_ICONIFY),
    JS_CGETSET_MAGIC_DEF("handleWindowMaximize", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_MAXIMIZE),
    JS_CGETSET_MAGIC_DEF(
        "handleFramebufferSize", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_FRAMEBUFFER_SIZE),
    JS_CGETSET_MAGIC_DEF(
        "handleWindowContentScale", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_CONTENT_SCALE),
    JS_CGETSET_MAGIC_DEF("handleMouseButton", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_MOUSE_BUTTON),
    JS_CGETSET_MAGIC_DEF("handleCursorPos", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CURSOR_POS),
    JS_CGETSET_MAGIC_DEF("handleCursorEnter", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CURSOR_ENTER),
    JS_CGETSET_MAGIC_DEF("handleScroll", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_SCROLL),
    JS_CGETSET_MAGIC_DEF("handleKey", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_KEY),
    JS_CGETSET_MAGIC_DEF("handleChar", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CHAR),
    JS_CGETSET_MAGIC_DEF("handleCharMods", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CHAR_MODS),
    JS_CGETSET_MAGIC_DEF("handleDrop", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_DROP),
    TRIGGER_FUNCTIONS(MAKE_TRIGGER_METHOD_ENTRY)
};

#undef MAKE_TRIGGER_METHOD_ENTRY

const JSCFunctionListEntry glfw_window_funcs[] = {
    JS_CFUNC_DEF("hint", 0, glfw_window_hint),
    JS_CFUNC_DEF("defaultHints", 0, glfw_window_default_hints),
};

#undef TRIGGER_FUNCTIONS

JSValue glfw_window_proto, glfw_window_class;

JSValue
glfw_window_constructor(JSContext* ctx) {
  JSRuntime* rt = JS_GetRuntime(ctx);

  if(!JS_IsRegisteredClass(rt, glfw_window_class_id)) {
    JS_NewClassID(&glfw_window_class_id);
    JS_NewClass(rt, glfw_window_class_id, &glfw_window_class_def);

    glfw_window_proto = JS_NewObject(ctx);
    JS_SetPropertyFunctionList(ctx, glfw_window_proto, glfw_window_proto_funcs, countof(glfw_window_proto_funcs));
    JS_SetClassProto(ctx, glfw_window_class_id, glfw_window_proto);

    glfw_window_class = JS_NewCFunction2(ctx, glfw_window_ctor, "Window", 5, JS_CFUNC_constructor, 0);
    JS_SetPropertyFunctionList(ctx, glfw_window_class, glfw_window_funcs, countof(glfw_window_funcs));
    JS_SetConstructor(ctx, glfw_window_class, glfw_window_proto);
  }

  return glfw_window_class;
}

JSValue
glfw_window_create_window(JSContext* ctx, int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
  GLFWwindow* window = glfwCreateWindow(width, height, title, monitor, share);
  WindowContext* wc;
  int i;
  if(window == NULL) {
    glfw_throw(ctx);
    return JS_EXCEPTION;
  }

  if((wc = js_mallocz(ctx, sizeof(WindowContext)))) {
    for(i = 0; i < _CALLBACK_LAST; i++) wc->handlers.list[i] = JS_UNDEFINED;

    wc->ctx = ctx;
  }
  glfwSetWindowUserPointer(window, wc);

  return glfw_window_new_instance(ctx, window);
}

JSValue
glfw_window_new_instance(JSContext* ctx, GLFWwindow* window) {
  JSValue obj = JS_UNDEFINED;
  JSValue proto;

  proto = JS_GetPropertyStr(ctx, glfw_window_class, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_window_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, window);

  return obj;
fail:
  JS_FreeValue(ctx, obj);
  return JS_EXCEPTION;
}

int
glfw_window_init(JSContext* ctx, JSModuleDef* m) {
  JS_SetModuleExport(ctx, m, "Window", glfw_window_constructor(ctx));
  return 0;
}

int
glfw_window_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Window");
}
