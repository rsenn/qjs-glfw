#include "glfw.h"
#include "monitor.h"
#include "position.h"
#include "size.h"

#include "window.h"

JSClassID glfw_window_class_id = 0;

/*

  const defaultCallbacks = {
    handlePos(x, y)  {
      console.log('handlePos', { x, y)  });
    },
    handleSize(width, height)  {
      console.log('handleSize', { width, height)  });
    },
    handleClose(w)  {
      console.log('handleClose', { w)  });
    },
    handleRefresh(w)  {
      console.log('handleRefresh', { w)  });
    },
    handleFocus(focused)  {
      console.log('handleFocus', { focused)  });
    },
    handleIconify(iconified)  {
      console.log('handleIconify', { iconified)  });
    },
    handleFramebufferSize(width, height)  {
      console.log('handleFramebufferSize', { width, height)  });
    },
    handleMouseButton(button, action, mods)  {
      console.log('handleMouseButton', { button, action, mods)  });
    },
    handleCursorPos(x, y)  {
      console.log('handleCursorPos', { x, y)  });
    },
    handleCursorEnter(cur)  {
      console.log('handleCursorEnter', { cur)  });
    },
    handleScroll(xoffset, yoffset)  {
      console.log('handleScroll', { xoffset, yoffset)  });
    },
    handleKey(key, scancode, action, mods)  {
      console.log('handleKey', { key, scancode, action, mods)  });
    },
    handleChar(c)  {
      console.log('handleChar', { c)  });
    },
    handleCharMods(c, mods)  {
      console.log('handleCharMods', { c, mods)  });
    },
    handleDrop(argcargv)  {
      console.log('handleDrop', { argcargv)  });
    }
  });

 */

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
      JSValue window_pos_handler, window_size_handler, window_close_handler, window_refresh_handler, window_focus_handler, window_iconify_handler, window_maximize_handler, framebuffer_size_handler,
          window_content_scale_handler, mouse_button_handler, cursor_pos_handler, cursor_enter_handler, scroll_handler, key_handler, char_handler, char_mods_handler, drop_handler;
    };
    JSValue list[_CALLBACK_LAST];
  } handlers;
  JSContext* ctx;
  JSValue this_val;
} WindowContext;

static void
glfw_handle_char(GLFWwindow* w, unsigned int c) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_CHAR];
  JSValueConst args[] = {JS_NewUint32(wc->ctx, c)};

  JS_Call(wc->ctx, callback, wc->this_val, 1, args);
}

static void
glfw_handle_charmods(GLFWwindow* w, unsigned int c, int mods) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_CHAR_MODS];
  JSValueConst args[] = {JS_NewUint32(wc->ctx, c), JS_NewInt32(wc->ctx, mods)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

static void
glfw_handle_cursorenter(GLFWwindow* w, int cur) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_CURSOR_ENTER];
  JSValueConst args[] = {JS_NewUint32(wc->ctx, cur)};

  JS_Call(wc->ctx, callback, wc->this_val, 1, args);
}

static void
glfw_handle_cursorpos(GLFWwindow* w, double x, double y) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_CURSOR_POS];
  JSValueConst args[] = {JS_NewInt32(wc->ctx, x), JS_NewInt32(wc->ctx, y)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

static void
glfw_handle_drop(GLFWwindow* w, int argc, const char* argv[]) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_DROP];
}

// static void glfw_handle_error(int,const char*) {}
static void
glfw_handle_framebuffersize(GLFWwindow* w, int width, int height) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_FRAMEBUFFER_SIZE];
  JSValueConst args[] = {JS_NewUint32(wc->ctx, width), JS_NewUint32(wc->ctx, height)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

// static void glfw_handle_joystick(int,int) {}
static void
glfw_handle_key(GLFWwindow* w, int key, int scancode, int action, int mods) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_KEY];
  JSValueConst args[] = {JS_NewInt32(wc->ctx, key), JS_NewInt32(wc->ctx, scancode), JS_NewInt32(wc->ctx, action), JS_NewInt32(wc->ctx, mods)};

  JS_Call(wc->ctx, callback, wc->this_val, 4, args);
}

/*static void
glfw_handle_monitor(GLFWmonitor* m, int event) {
  WindowContext* wc = glfwGetMonitorUserPointer(w);
}
*/
static void
glfw_handle_mousebutton(GLFWwindow* w, int button, int action, int mods) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_MOUSE_BUTTON];
  JSValueConst args[] = {JS_NewInt32(wc->ctx, button), JS_NewInt32(wc->ctx, action), JS_NewInt32(wc->ctx, mods)};

  JS_Call(wc->ctx, callback, wc->this_val, 3, args);
}

static void
glfw_handle_scroll(GLFWwindow* w, double xoffset, double yoffset) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_SCROLL];
  JSValueConst args[] = {JS_NewFloat64(wc->ctx, xoffset), JS_NewFloat64(wc->ctx, yoffset)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

static void
glfw_handle_windowclose(GLFWwindow* w) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_CLOSE];
  JSValueConst args[] = {JS_UNDEFINED};

  JS_Call(wc->ctx, callback, wc->this_val, 0, args);
}

static void
glfw_handle_windowcontentscale(GLFWwindow* w, float sx, float sy) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_CONTENT_SCALE];
  JSValueConst args[] = {JS_NewFloat64(wc->ctx, sx), JS_NewFloat64(wc->ctx, sy)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

static void
glfw_handle_windowfocus(GLFWwindow* w, int focused) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_FOCUS];
  JSValueConst args[] = {JS_NewBool(wc->ctx, focused)};

  JS_Call(wc->ctx, callback, wc->this_val, 1, args);
}

static void
glfw_handle_windowiconify(GLFWwindow* w, int iconified) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_ICONIFY];
  JSValueConst args[] = {JS_NewBool(wc->ctx, iconified)};

  JS_Call(wc->ctx, callback, wc->this_val, 1, args);
}

static void
glfw_handle_windowmaximize(GLFWwindow* w, int iconified) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_MAXIMIZE];
  JSValueConst args[] = {JS_NewBool(wc->ctx, iconified)};

  JS_Call(wc->ctx, callback, wc->this_val, 1, args);
}

static void
glfw_handle_windowpos(GLFWwindow* w, int x, int y) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_POS];
  JSValueConst args[] = {JS_NewInt32(wc->ctx, x), JS_NewInt32(wc->ctx, y)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

static void
glfw_handle_windowrefresh(GLFWwindow* w) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_REFRESH];
  JSValueConst args[] = {JS_UNDEFINED};

  JS_Call(wc->ctx, callback, wc->this_val, 0, args);
}

static void
glfw_handle_windowsize(GLFWwindow* w, int width, int height) {
  WindowContext* wc = glfwGetWindowUserPointer(w);
  JSValue callback = wc->handlers.list[CALLBACK_WINDOW_SIZE];
  JSValueConst args[] = {JS_NewUint32(wc->ctx, width), JS_NewUint32(wc->ctx, height)};

  JS_Call(wc->ctx, callback, wc->this_val, 2, args);
}

// constructor/destructor
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

// instance methods
JSValue
glfw_window_make_context_current(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;
  glfwMakeContextCurrent(window);
  return JS_UNDEFINED;
}

JSValue
glfw_window_swap_buffers(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;
  glfwSwapBuffers(window);
  return JS_UNDEFINED;
}

// static methods
JSValue
glfw_window_hint(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
  int key;

  if(JS_ToInt32(ctx, &key, argv[0]))
    return JS_EXCEPTION;

  if(JS_IsString(argv[1])) {
    const char* value = JS_ToCString(ctx, argv[1]);
#ifdef HAVE_GLFW_WINDOW_HINT_STRING
    glfwWindowHintString(key, value);
#endif
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

// properties
JSValue
glfw_window_get_should_close(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  if(glfwWindowShouldClose(window))
    return JS_TRUE;
  else
    return JS_FALSE;
}

JSValue
glfw_window_set_should_close(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;
  int shouldClose = JS_VALUE_GET_BOOL(value) == 1 ? GL_TRUE : GL_FALSE;
  glfwSetWindowShouldClose(window, shouldClose);
  return JS_UNDEFINED;
}

JSValue
glfw_window_set_title(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
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
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  GLFWposition* position = JS_GetOpaque2(ctx, value, glfw_position_class_id);
  if(!position)
    return JS_EXCEPTION;

  glfwSetWindowPos(window, position->x, position->y);
  return JS_UNDEFINED;
}

JSValue
glfw_window_get_position(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  GLFWposition* position = js_mallocz(ctx, sizeof(*position));
  glfwGetWindowPos(window, &position->x, &position->y);
  return glfw_position_new_instance(ctx, position);
}

// TODO: magic these with position setter/getter?
JSValue
glfw_window_set_size(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  GLFWsize* size = JS_GetOpaque2(ctx, value, glfw_size_class_id);
  if(!size)
    return JS_EXCEPTION;

  glfwSetWindowSize(window, size->width, size->height);
  return JS_UNDEFINED;
}

JSValue
glfw_window_get_size(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  GLFWsize* size = js_mallocz(ctx, sizeof(*size));
  glfwGetWindowSize(window, &size->width, &size->height);
  return glfw_size_new_instance(ctx, size);
}

JSValue
glfw_window_get_framebuffer_size(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  GLFWsize* size = js_mallocz(ctx, sizeof(*size));
  glfwGetFramebufferSize(window, &size->width, &size->height);
  return glfw_size_new_instance(ctx, size);
}

JSValue
glfw_window_set_opacity(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;

  double opacity;
  if(JS_ToFloat64(ctx, &opacity, value))
    return JS_EXCEPTION;

#ifdef HAVE_GLFW_SET_WINDOW_OPACITY
  glfwSetWindowOpacity(window, opacity);
#endif
  return JS_UNDEFINED;
}

JSValue
glfw_window_get_opacity(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  if(!window)
    return JS_EXCEPTION;
#ifdef HAVE_GLFW_GET_WINDOW_OPACITY
  return JS_NewFloat64(ctx, glfwGetWindowOpacity(window));
#else
  return JS_UNDEFINED;
#endif
}

JSValue
glfw_window_get_monitor(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
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
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  WindowContext* wc;
  if(!window)
    return JS_EXCEPTION;

  if((wc = glfwGetWindowUserPointer(window)))
    return JS_DupValue(ctx, wc->handlers.list[magic]);

  return JS_UNDEFINED;
}

JSValue
glfw_window_get_id(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;
  WindowContext* wc;
  char buf[128];

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  snprintf(buf, sizeof(buf), "%p", window);

  return JS_NewString(ctx, buf);
}

JSValue
glfw_window_set_callback(JSContext* ctx, JSValueConst this_val, JSValueConst value, int magic) {
  GLFWwindow* window = glfw_window_data2(ctx, this_val);
  WindowContext* wc;
  BOOL enable;
  JSValue ret = JS_UNDEFINED;

  if(!window)
    return JS_EXCEPTION;

  if((wc = glfwGetWindowUserPointer(window))) {
    if(!JS_IsUndefined(wc->handlers.list[magic]))
      JS_FreeValue(ctx, wc->handlers.list[magic]);

    wc->handlers.list[magic] = JS_DupValue(ctx, value);

    enable = JS_IsFunction(ctx, wc->handlers.list[magic]);

    ret = JS_NewBool(ctx, enable);

    switch(magic) {
      case CALLBACK_WINDOW_POS: {
        glfwSetWindowPosCallback(window, enable ? &glfw_handle_windowpos : 0);
        break;
      }
      case CALLBACK_WINDOW_SIZE: {
        glfwSetWindowSizeCallback(window, enable ? &glfw_handle_windowsize : 0);
        break;
      }
      case CALLBACK_WINDOW_CLOSE: {
        glfwSetWindowCloseCallback(window, enable ? &glfw_handle_windowclose : 0);
        break;
      }
      case CALLBACK_WINDOW_REFRESH: {
        glfwSetWindowRefreshCallback(window, enable ? &glfw_handle_windowrefresh : 0);
        break;
      }
      case CALLBACK_WINDOW_FOCUS: {
        glfwSetWindowFocusCallback(window, enable ? &glfw_handle_windowfocus : 0);
        break;
      }
      case CALLBACK_WINDOW_ICONIFY: {
        glfwSetWindowIconifyCallback(window, enable ? &glfw_handle_windowiconify : 0);
        break;
      }
      case CALLBACK_WINDOW_MAXIMIZE: {
#ifdef HAVE_GLFW_SET_WINDOW_MAXIMIZE_CALLBACK
        glfwSetWindowMaximizeCallback(window, enable ? &glfw_handle_windowmaximize : 0);
#endif
        break;
      }
      case CALLBACK_FRAMEBUFFER_SIZE: {
        glfwSetFramebufferSizeCallback(window, enable ? &glfw_handle_framebuffersize : 0);
        break;
      }
      case CALLBACK_WINDOW_CONTENT_SCALE: {
#ifdef HAVE_GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK
        glfwSetWindowContentScaleCallback(window, enable ? &glfw_handle_windowcontentscale : 0);
#endif
        break;
      }
      case CALLBACK_MOUSE_BUTTON: {
        glfwSetMouseButtonCallback(window, enable ? &glfw_handle_mousebutton : 0);
        break;
      }
      case CALLBACK_CURSOR_POS: {
        glfwSetCursorPosCallback(window, enable ? &glfw_handle_cursorpos : 0);
        break;
      }
      case CALLBACK_CURSOR_ENTER: {
        glfwSetCursorEnterCallback(window, enable ? &glfw_handle_cursorenter : 0);
        break;
      }
      case CALLBACK_SCROLL: {
        glfwSetScrollCallback(window, enable ? &glfw_handle_scroll : 0);
        break;
      }
      case CALLBACK_KEY: {
        glfwSetKeyCallback(window, enable ? &glfw_handle_key : 0);
        break;
      }
      case CALLBACK_CHAR: {
        glfwSetCharCallback(window, enable ? &glfw_handle_char : 0);
        break;
      }
      case CALLBACK_CHAR_MODS: {
        glfwSetCharModsCallback(window, enable ? &glfw_handle_charmods : 0);
        break;
      }
      case CALLBACK_DROP: {
        glfwSetDropCallback(window, enable ? &glfw_handle_drop : 0);
        break;
      }
    }
  }

  return ret;
}

// Generate a few simple methods with macros...because I'm lazy. :O
#define TRIGGER_FUNCTIONS(V) \
  V(IconifyWindow, iconify) \
  V(RestoreWindow, restore) \
  V(MaximizeWindow, maximize) \
  V(ShowWindow, show) \
  V(HideWindow, hide) \
  V(FocusWindow, focus)

#define MAKE_TRIGGER_METHOD(NativeName, JSName) \
  JSValue glfw_window_##JSName(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) { \
    GLFWwindow* window = glfw_window_data2(ctx, this_val); \
    glfw##NativeName(window); \
    if(!window) \
      return JS_EXCEPTION; \
    return JS_UNDEFINED; \
  }
TRIGGER_FUNCTIONS(MAKE_TRIGGER_METHOD)
#ifdef HAVE_GLFW_REQUEST_WINDOW_ATTENTION
MAKE_TRIGGER_METHOD(RequestWindowAttention, requestAttention)
#endif
#undef MAKE_TRIGGER_METHOD

// initialization
JSClassDef glfw_window_class_def = {
    .class_name = "Window",
};

#define MAKE_TRIGGER_METHOD_ENTRY(NativeName, JSName) JS_CFUNC_DEF(#JSName, 0, glfw_window_##JSName),

/*#define JS_CGETSET_ENUMERABLE_DEF(prop_name, fgetter, fsetter, magic_num) \
  { \
    .name = prop_name, .prop_flags = JS_PROP_ENUMERABLE | JS_PROP_CONFIGURABLE, .def_type = JS_DEF_CGETSET_MAGIC, .magic = magic_num, .u = { \
      .getset = {.get = {.getter_magic = fgetter}, .set = {.setter_magic = fsetter}} \
    } \
  }
*/

const JSCFunctionListEntry glfw_window_proto_funcs[] = {
    JS_CFUNC_DEF("makeContextCurrent", 0, glfw_window_make_context_current),
    JS_CFUNC_DEF("swapBuffers", 0, glfw_window_swap_buffers),
    JS_CGETSET_DEF("shouldClose", glfw_window_get_should_close, glfw_window_set_should_close),
    JS_CGETSET_ENUMERABLE_DEF("title", NULL, glfw_window_set_title),
    JS_CGETSET_ENUMERABLE_DEF("position", glfw_window_get_position, glfw_window_set_position),
    JS_CGETSET_ENUMERABLE_DEF("size", glfw_window_get_size, glfw_window_set_size),
    JS_CGETSET_DEF("framebufferSize", glfw_window_get_framebuffer_size, NULL),
    JS_CGETSET_DEF("opacity", glfw_window_get_opacity, glfw_window_set_opacity),
    JS_CGETSET_DEF("monitor", glfw_window_get_monitor, NULL),
    JS_CGETSET_ENUMERABLE_DEF("id", glfw_window_get_id, NULL),
    JS_CGETSET_MAGIC_DEF("handlePos", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_POS),
    JS_CGETSET_MAGIC_DEF("handleSize", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_SIZE),
    JS_CGETSET_MAGIC_DEF("handleClose", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_CLOSE),
    JS_CGETSET_MAGIC_DEF("handleRefresh", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_REFRESH),
    JS_CGETSET_MAGIC_DEF("handleFocus", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_FOCUS),
    JS_CGETSET_MAGIC_DEF("handleIconify", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_ICONIFY),
    JS_CGETSET_MAGIC_DEF("handleMaximize", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_MAXIMIZE),
    JS_CGETSET_MAGIC_DEF("handleFramebufferSize", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_FRAMEBUFFER_SIZE),
    JS_CGETSET_MAGIC_DEF("handleContentScale", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_WINDOW_CONTENT_SCALE),
    JS_CGETSET_MAGIC_DEF("handleMouseButton", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_MOUSE_BUTTON),
    JS_CGETSET_MAGIC_DEF("handleCursorPos", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CURSOR_POS),
    JS_CGETSET_MAGIC_DEF("handleCursorEnter", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CURSOR_ENTER),
    JS_CGETSET_MAGIC_DEF("handleScroll", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_SCROLL),
    JS_CGETSET_MAGIC_DEF("handleKey", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_KEY),
    JS_CGETSET_MAGIC_DEF("handleChar", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CHAR),
    JS_CGETSET_MAGIC_DEF("handleCharMods", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_CHAR_MODS),
    JS_CGETSET_MAGIC_DEF("handleDrop", glfw_window_get_callback, glfw_window_set_callback, CALLBACK_DROP),
    //  TRIGGER_FUNCTIONS(MAKE_TRIGGER_METHOD_ENTRY)
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWwindow", JS_PROP_CONFIGURABLE),
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
  if(window == NULL) {
#ifdef HAVE_GLFW_GET_ERROR
    glfw_throw(ctx);
    return JS_EXCEPTION;
#else
    return JS_ThrowInternalError(ctx, "glfwCreateWindow failed");
#endif
  }

  return glfw_window_new_instance(ctx, window);
}

JSValue
glfw_window_new_instance(JSContext* ctx, GLFWwindow* window) {
  JSValue obj = JS_UNDEFINED;
  JSValue proto;
  WindowContext* wc;

  proto = JS_GetPropertyStr(ctx, glfw_window_class, "prototype");
  if(JS_IsException(proto))
    goto fail;

  obj = JS_NewObjectProtoClass(ctx, proto, glfw_window_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj))
    goto fail;

  JS_SetOpaque(obj, window);

  if((wc = js_mallocz(ctx, sizeof(WindowContext)))) {
    int i;
    for(i = 0; i < _CALLBACK_LAST; i++) wc->handlers.list[i] = JS_UNDEFINED;

    wc->ctx = ctx;
    wc->this_val = JS_DupValue(ctx, obj);
  }

  glfwSetWindowUserPointer(window, wc);

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
