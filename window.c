#include "glfw.h"
#include "monitor.h"
#include "position.h"
#include "size.h"
#include "image.h"
#include "window.h"

JSClassID glfw_window_class_id = 0;
JSValue glfw_window_proto, glfw_window_class;

/*const defaultCallbacks = {
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
});*/

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
  JSContext* ctx;
  JSValue this_val;
  union {
    struct {
      JSValue window_pos_handler, window_size_handler, window_close_handler, window_refresh_handler, window_focus_handler, window_iconify_handler, window_maximize_handler, framebuffer_size_handler,
          window_content_scale_handler, mouse_button_handler, cursor_pos_handler, cursor_enter_handler, scroll_handler, key_handler, char_handler, char_mods_handler, drop_handler;
    };
    JSValue list[_CALLBACK_LAST];
  } handlers;
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
  JSValueConst args[argc];

  for(int i = 0; i < argc; i++)
    args[i] = JS_NewString(wc->ctx, argv[i]);

  JS_Call(wc->ctx, callback, wc->this_val, argc, args);

  for(int i = 0; i < argc; i++)
    JS_FreeValue(wc->ctx, args[i]);
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

static JSValue
glfw_window_new(JSContext* ctx, int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
  GLFWwindow* window;

  if(!glfw_initialized)
    if(!glfw_initialize(ctx)) {
#ifdef HAVE_GLFW_GET_ERROR
      return GLFW_THROW();
#endif
    }

  if((window = glfwCreateWindow(width, height, title ? title : "qjs-glfw", monitor, share)) == NULL) {
#ifdef HAVE_GLFW_GET_ERROR
    return GLFW_THROW();
#else
    return JS_ThrowInternalError(ctx, "glfwCreateWindow failed");
#endif
  }

  return glfw_window_wrap(ctx, window);
}

// constructor/destructor
static JSValue
glfw_window_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  int32_t width, height;
  const char* title = 0;
  GLFWsize* size;
  GLFWmonitor* monitor = NULL;
  GLFWwindow* share = NULL;
  JSValue ret;
  int i = 0;

  if(JS_IsObject(argv[i]) && (size = JS_GetOpaque(argv[i], glfw_size_class_id))) {
    width = size->width;
    height = size->height;

    ++i;
  } else {
    if(JS_ToInt32(ctx, &width, argv[i]))
      return JS_ThrowTypeError(ctx, "argument 1 (width) must be a number");

    if(JS_ToInt32(ctx, &height, argv[i + 1]))
      return JS_ThrowTypeError(ctx, "argument 2 (height) must be a number");

    i += 2;
  }

  if(argc > i) {
    if(JS_IsNull(argv[i]) || JS_IsUndefined(argv[i]))
      title = 0;
    else if(!(title = JS_ToCString(ctx, argv[i])))
      return JS_ThrowTypeError(ctx, "argument %d (title) must be a string", i + 1);

    if(++i < argc) {
      if(JS_IsNull(argv[i]) || JS_IsUndefined(argv[i]))
        monitor = 0;
      else if(!(monitor = JS_GetOpaque(argv[i], glfw_monitor_class_id)))
        return JS_ThrowTypeError(ctx, "argument %d (monitor) must be a glfw.Monitor or null|undefined", i + 1);

      if(++i < argc) {
        if(JS_IsNull(argv[i]) || JS_IsUndefined(argv[i]))
          share = 0;
        else if(!(share = JS_GetOpaque(argv[i], glfw_window_class_id)))
          return JS_ThrowTypeError(ctx, "argument %d (share) must be a glfw.Window or null|undefined", i + 1);
      }
    }
  }

  ret = glfw_window_new(ctx, width, height, title, monitor, share);

  if(title)
    JS_FreeCString(ctx, title);

  return ret;
}

// instance methods
static JSValue
glfw_window_get_id(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  return js_newptr(ctx, window);
}

static JSValue
glfw_window_make_context_current(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  glfwMakeContextCurrent(window);
  return JS_UNDEFINED;
}

static JSValue
glfw_window_swap_buffers(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  glfwSwapBuffers(window);
  return JS_UNDEFINED;
}

// static methods
static JSValue
glfw_window_hint(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
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

static JSValue
glfw_window_default_hints(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  glfwDefaultWindowHints();
  return JS_UNDEFINED;
}

// properties
static JSValue
glfw_window_get_should_close(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  return glfwWindowShouldClose(window) ? JS_TRUE : JS_FALSE;
}

static JSValue
glfw_window_set_should_close(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  int shouldClose = JS_VALUE_GET_BOOL(value) == 1 ? GL_TRUE : GL_FALSE;
  glfwSetWindowShouldClose(window, shouldClose);
  return JS_UNDEFINED;
}

static JSValue
glfw_window_set_title(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if(!JS_IsString(value)) {
    JS_ThrowTypeError(ctx, "Title must be a string");
    return JS_EXCEPTION;
  }

  const char* title = JS_ToCString(ctx, value);
  glfwSetWindowTitle(window, title);
  return JS_UNDEFINED;
}

static JSValue
glfw_window_set_position(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window;
  GLFWposition* position;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if(!(position = JS_GetOpaque2(ctx, value, glfw_position_class_id)))
    return JS_EXCEPTION;

  glfwSetWindowPos(window, position->x, position->y);
  return JS_UNDEFINED;
}

static JSValue
glfw_window_get_position(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;
  GLFWposition* position;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if(!(position = js_mallocz(ctx, sizeof(*position))))
    return JS_EXCEPTION;

  glfwGetWindowPos(window, &position->x, &position->y);
  return glfw_position_wrap(ctx, position);
}

// TODO: magic these with position setter/getter?
static JSValue
glfw_window_set_size(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  GLFWsize* size = JS_GetOpaque2(ctx, value, glfw_size_class_id);
  if(!size)
    return JS_EXCEPTION;

  glfwSetWindowSize(window, size->width, size->height);
  return JS_UNDEFINED;
}

static JSValue
glfw_window_get_size(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  GLFWsize* size = js_mallocz(ctx, sizeof(*size));
  glfwGetWindowSize(window, &size->width, &size->height);
  return glfw_size_wrap(ctx, size);
}

static JSValue
glfw_window_get_framebuffer_size(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  GLFWsize* size = js_mallocz(ctx, sizeof(*size));
  glfwGetFramebufferSize(window, &size->width, &size->height);
  return glfw_size_wrap(ctx, size);
}

static JSValue
glfw_window_set_opacity(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  double opacity;
  if(JS_ToFloat64(ctx, &opacity, value))
    return JS_EXCEPTION;

#ifdef HAVE_GLFW_SET_WINDOW_OPACITY
  glfwSetWindowOpacity(window, opacity);
#endif
  return JS_UNDEFINED;
}

static JSValue
glfw_window_get_opacity(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

#ifdef HAVE_GLFW_GET_WINDOW_OPACITY
  return JS_NewFloat64(ctx, glfwGetWindowOpacity(window));
#else
  return JS_UNDEFINED;
#endif
}

static JSValue
glfw_window_get_monitor(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;
  GLFWmonitor* monitor;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if(!(monitor = glfwGetWindowMonitor(window)))
    return JS_NULL;

  return glfw_monitor_wrap(ctx, monitor);
}

static JSValue
glfw_window_set_monitor(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) {
  GLFWwindow* window;
  GLFWmonitor* monitor;

  int32_t xpos = 0, ypos = 0, width = 0, height = 0, refreshRate = GLFW_DONT_CARE;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if(JS_IsNull(argv[0]) || JS_IsUndefined(argv[0]))
    monitor = NULL;
  else if(!(monitor = JS_GetOpaque(argv[0], glfw_monitor_class_id)))
    return JS_ThrowTypeError(ctx, "argument 1 must be a glfw.Monitor or null|undefined");

  if(argc > 1)
    JS_ToInt32(ctx, &xpos, argv[1]);
  if(argc > 2)
    JS_ToInt32(ctx, &ypos, argv[2]);
  if(argc > 3)
    JS_ToInt32(ctx, &width, argv[3]);
  if(argc > 4)
    JS_ToInt32(ctx, &height, argv[4]);
  if(argc > 5)
    JS_ToInt32(ctx, &refreshRate, argv[5]);

  glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate);

  return JS_UNDEFINED;
}

static JSValue
glfw_window_get_cursor_pos(JSContext* ctx, JSValueConst this_val) {
  GLFWwindow* window;
  struct {
    double x, y;
  } pos;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  glfwGetCursorPos(window, &pos.x, &pos.y);

  JSValue ret = JS_NewObject(ctx);

  JS_SetPropertyStr(ctx, ret, "x", JS_NewFloat64(ctx, pos.x));
  JS_SetPropertyStr(ctx, ret, "y", JS_NewFloat64(ctx, pos.y));
  return ret;
}

static JSValue
glfw_window_set_cursor_pos(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWwindow* window;
  struct {
    double x, y;
  } pos;
  JSValue x, y;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if(JS_IsArray(ctx, value)) {
    x = JS_GetPropertyUint32(ctx, value, 0);
    y = JS_GetPropertyUint32(ctx, value, 1);
  } else {
    x = JS_GetPropertyStr(ctx, value, "x");
    y = JS_GetPropertyStr(ctx, value, "y");
  }

  JS_ToFloat64(ctx, &pos.x, x);
  JS_FreeValue(ctx, x);
  JS_ToFloat64(ctx, &pos.y, y);
  JS_FreeValue(ctx, y);

  glfwSetCursorPos(window, pos.x, pos.y);
  return JS_UNDEFINED;
}

static JSValue
glfw_window_get_callback(JSContext* ctx, JSValueConst this_val, int magic) {
  GLFWwindow* window;
  WindowContext* wc;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  if((wc = glfwGetWindowUserPointer(window)))
    return JS_DupValue(ctx, wc->handlers.list[magic]);

  return JS_UNDEFINED;
}

static JSValue
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

enum {
  SET_WINDOW_SIZE_LIMITS,
  SET_WINDOW_ASPECT_RATIO,
  GET_WINDOW_FRAME_SIZE,
  GET_WINDOW_CONTENT_SCALE,
  GET_WINDOW_ATTRIB,
  SET_WINDOW_ATTRIB,
  SET_CURSOR,
  SET_WINDOW_ICON,
  GET_MOUSE_BUTTON,
  SET_CLIPBOARD_STRING,
  GET_CLIPBOARD_STRING,
  GET_INPUT_MODE,
  SET_INPUT_MODE,
  GET_KEY,
  DESTROY_WINDOW,
};

static JSValue
glfw_window_functions(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[], int magic) {
  GLFWwindow* window;
  JSValue ret = JS_UNDEFINED;

  if(!(window = glfw_window_data2(ctx, this_val)))
    return JS_EXCEPTION;

  switch(magic) {
    case SET_WINDOW_SIZE_LIMITS: {
      int32_t minw = 0, minh = 0, maxw = 0, maxh = 0;

      JS_ToInt32(ctx, &minw, argv[0]);
      JS_ToInt32(ctx, &minh, argv[1]);
      JS_ToInt32(ctx, &maxw, argv[2]);
      JS_ToInt32(ctx, &maxh, argv[3]);

      glfwSetWindowSizeLimits(window, minw, minh, maxw, maxh);
      break;
    }

    case SET_WINDOW_ASPECT_RATIO: {
      int32_t numer = 0, denom = 0;

      JS_ToInt32(ctx, &numer, argv[0]);
      JS_ToInt32(ctx, &denom, argv[1]);

      glfwSetWindowAspectRatio(window, numer, denom);
      break;
    }

    case GET_WINDOW_FRAME_SIZE: {
      int left, top, right, bottom;

      glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);

      ret = argc > 0 && JS_IsObject(argv[0]) ? JS_DupValue(ctx, argv[0]) : JS_NewArray(ctx);

      if(JS_IsArray(ctx, ret)) {
        JS_SetPropertyUint32(ctx, ret, 0, JS_NewInt32(ctx, left));
        JS_SetPropertyUint32(ctx, ret, 1, JS_NewInt32(ctx, top));
        JS_SetPropertyUint32(ctx, ret, 2, JS_NewInt32(ctx, right));
        JS_SetPropertyUint32(ctx, ret, 3, JS_NewInt32(ctx, bottom));
      } else {
        JS_SetPropertyStr(ctx, ret, "left", JS_NewInt32(ctx, left));
        JS_SetPropertyStr(ctx, ret, "top", JS_NewInt32(ctx, top));
        JS_SetPropertyStr(ctx, ret, "right", JS_NewInt32(ctx, right));
        JS_SetPropertyStr(ctx, ret, "bottom", JS_NewInt32(ctx, bottom));
      }

      break;
    }

    case GET_WINDOW_CONTENT_SCALE: {
      float xscale, yscale;

      glfwGetWindowContentScale(window, &xscale, &yscale);

      ret = argc > 0 && JS_IsObject(argv[0]) ? JS_DupValue(ctx, argv[0]) : JS_NewArray(ctx);

      if(JS_IsArray(ctx, ret)) {
        JS_SetPropertyUint32(ctx, ret, 0, JS_NewFloat64(ctx, xscale));
        JS_SetPropertyUint32(ctx, ret, 1, JS_NewFloat64(ctx, yscale));
      } else {
        JS_SetPropertyStr(ctx, ret, "x", JS_NewFloat64(ctx, xscale));
        JS_SetPropertyStr(ctx, ret, "y", JS_NewFloat64(ctx, yscale));
      }

      break;
    }

    case GET_WINDOW_ATTRIB: {
      int32_t attrib = -1;

      JS_ToInt32(ctx, &attrib, argv[0]);

      ret = JS_NewInt32(ctx, glfwGetWindowAttrib(window, attrib));
      break;
    }

    case SET_WINDOW_ATTRIB: {
      int32_t attrib = -1, value = -1;

      JS_ToInt32(ctx, &attrib, argv[0]);
      JS_ToInt32(ctx, &value, argv[1]);

      glfwSetWindowAttrib(window, attrib, value);
      break;
    }

    case SET_CURSOR: {
      GLFWcursor* cursor = js_getptr(ctx, argv[0]);

      glfwSetCursor(window, cursor);
      break;
    }

    case SET_WINDOW_ICON: {
      GLFWimage *im, images[argc];

      for(int i = 0; i < argc; i++) {
        if(!(im = JS_GetOpaque(argv[i], glfw_image_class_id)))
          return JS_ThrowTypeError(ctx, "argument %d must be a glfw.Image", i + 1);

        images[i] = *im;
      }

      glfwSetWindowIcon(window, argc, (GLFWimage const*)images);
      break;
    }

    case GET_MOUSE_BUTTON: {
      int32_t button = -1;
      JS_ToInt32(ctx, &button, argv[0]);

      ret = JS_NewInt32(ctx, glfwGetMouseButton(window, button));
      break;
    }

    case GET_CLIPBOARD_STRING: {
      const char* str;

      if((str = glfwGetClipboardString(window)))
        ret = JS_NewString(ctx, str);
      break;
    }

    case SET_CLIPBOARD_STRING: {
      const char* str;

      if(!(str = JS_ToCString(ctx, argv[0])))
        return JS_ThrowTypeError(ctx, "argument 1 must be a string");

      glfwSetClipboardString(window, str);
      break;
    }

    case GET_INPUT_MODE: {
      int32_t mode = -1;
      JS_ToInt32(ctx, &mode, argv[0]);

      ret = JS_NewInt32(ctx, glfwGetInputMode(window, mode));
      break;
    }

    case SET_INPUT_MODE: {
      int32_t mode = -1, value = GLFW_FALSE;
      JS_ToInt32(ctx, &mode, argv[0]);
      JS_ToInt32(ctx, &value, argv[1]);

      glfwSetInputMode(window, mode, value);
      break;
    }

    case GET_KEY: {
      int32_t key = -1;
      JS_ToInt32(ctx, &key, argv[0]);

      ret = JS_NewInt32(ctx, glfwGetKey(window, key));
      break;
    }

    case DESTROY_WINDOW: {
      glfwDestroyWindow(window);
      JS_SetOpaque(this_val, NULL);
      break;
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
  static JSValue glfw_window_##JSName(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst argv[]) { \
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
static JSClassDef glfw_window_class_def = {
    .class_name = "Window",
};

#define MAKE_TRIGGER_METHOD_ENTRY(NativeName, JSName) JS_CFUNC_DEF(#JSName, 0, glfw_window_##JSName),

static const JSCFunctionListEntry glfw_window_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_DEF("id", glfw_window_get_id, NULL),
    JS_CFUNC_DEF("makeContextCurrent", 0, glfw_window_make_context_current),
    JS_CFUNC_DEF("swapBuffers", 0, glfw_window_swap_buffers),
    JS_CGETSET_DEF("shouldClose", glfw_window_get_should_close, glfw_window_set_should_close),
    JS_CGETSET_DEF("title", NULL, glfw_window_set_title),
    JS_CGETSET_ENUMERABLE_DEF("position", glfw_window_get_position, glfw_window_set_position),
    JS_CGETSET_ENUMERABLE_DEF("size", glfw_window_get_size, glfw_window_set_size),
    JS_CGETSET_DEF("framebufferSize", glfw_window_get_framebuffer_size, NULL),
    JS_CGETSET_DEF("opacity", glfw_window_get_opacity, glfw_window_set_opacity),
    JS_CGETSET_DEF("monitor", glfw_window_get_monitor, 0),
    JS_CGETSET_DEF("cursorPos", glfw_window_get_cursor_pos, glfw_window_set_cursor_pos),
    JS_CFUNC_DEF("setMonitor", 1, glfw_window_set_monitor),
    JS_CFUNC_MAGIC_DEF("setSizeLimits", 4, glfw_window_functions, SET_WINDOW_SIZE_LIMITS),
    JS_CFUNC_MAGIC_DEF("setAspectRatio", 2, glfw_window_functions, SET_WINDOW_ASPECT_RATIO),
    JS_CFUNC_MAGIC_DEF("getFrameSize", 0, glfw_window_functions, GET_WINDOW_FRAME_SIZE),
    JS_CFUNC_MAGIC_DEF("getContentScale", 0, glfw_window_functions, GET_WINDOW_CONTENT_SCALE),
    JS_CFUNC_MAGIC_DEF("getAttrib", 1, glfw_window_functions, GET_WINDOW_ATTRIB),
    JS_CFUNC_MAGIC_DEF("setAttrib", 2, glfw_window_functions, SET_WINDOW_ATTRIB),
    JS_CFUNC_MAGIC_DEF("setCursor", 1, glfw_window_functions, SET_CURSOR),
    JS_CFUNC_MAGIC_DEF("setIcon", 1, glfw_window_functions, SET_WINDOW_ICON),
    JS_CFUNC_MAGIC_DEF("getMouseButton", 1, glfw_window_functions, GET_MOUSE_BUTTON),
    JS_CFUNC_MAGIC_DEF("getClipboardString", 0, glfw_window_functions, GET_CLIPBOARD_STRING),
    JS_CFUNC_MAGIC_DEF("setClipboardString", 1, glfw_window_functions, SET_CLIPBOARD_STRING),
    JS_CFUNC_MAGIC_DEF("getInputMode", 0, glfw_window_functions, GET_INPUT_MODE),
    JS_CFUNC_MAGIC_DEF("setInputMode", 1, glfw_window_functions, SET_INPUT_MODE),
    JS_CFUNC_MAGIC_DEF("getKey", 1, glfw_window_functions, GET_KEY),
    JS_CFUNC_MAGIC_DEF("destroy", 0, glfw_window_functions, DESTROY_WINDOW),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWwindow", JS_PROP_CONFIGURABLE),
};

static const JSCFunctionListEntry glfw_window_proto_trigfuncs[] = {
#ifdef HAVE_GLFW_REQUEST_WINDOW_ATTENTION
    MAKE_TRIGGER_METHOD_ENTRY(RequestWindowAttention, requestAttention)
#endif
        TRIGGER_FUNCTIONS(MAKE_TRIGGER_METHOD_ENTRY)};

#define GETSET_HANDLER(name, const) JS_CGETSET_MAGIC_DEF((#name), glfw_window_get_callback, glfw_window_set_callback, CALLBACK_##const)

static const JSCFunctionListEntry glfw_window_proto_handlers[] = {
    GETSET_HANDLER(handlePos, WINDOW_POS),
    GETSET_HANDLER(handleSize, WINDOW_SIZE),
    GETSET_HANDLER(handleClose, WINDOW_CLOSE),
    GETSET_HANDLER(handleRefresh, WINDOW_REFRESH),
    GETSET_HANDLER(handleFocus, WINDOW_FOCUS),
    GETSET_HANDLER(handleIconify, WINDOW_ICONIFY),
    GETSET_HANDLER(handleMaximize, WINDOW_MAXIMIZE),
    GETSET_HANDLER(handleFramebufferSize, FRAMEBUFFER_SIZE),
    GETSET_HANDLER(handleContentScale, WINDOW_CONTENT_SCALE),
    GETSET_HANDLER(handleMouseButton, MOUSE_BUTTON),
    GETSET_HANDLER(handleCursorPos, CURSOR_POS),
    GETSET_HANDLER(handleCursorEnter, CURSOR_ENTER),
    GETSET_HANDLER(handleScroll, SCROLL),
    GETSET_HANDLER(handleKey, KEY),
    GETSET_HANDLER(handleChar, CHAR),
    GETSET_HANDLER(handleCharMods, CHAR_MODS),
    GETSET_HANDLER(handleDrop, DROP),
};

#undef MAKE_TRIGGER_METHOD_ENTRY

static const JSCFunctionListEntry glfw_window_funcs[] = {
    JS_CFUNC_DEF("hint", 0, glfw_window_hint),
    JS_CFUNC_DEF("defaultHints", 0, glfw_window_default_hints),
};

#undef TRIGGER_FUNCTIONS

JSValue
glfw_window_wrap(JSContext* ctx, GLFWwindow* window) {
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
    for(i = 0; i < _CALLBACK_LAST; i++)
      wc->handlers.list[i] = JS_UNDEFINED;

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

  JS_NewClassID(&glfw_window_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_window_class_id, &glfw_window_class_def);

  glfw_window_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_window_proto, glfw_window_proto_funcs, countof(glfw_window_proto_funcs));
  JS_SetPropertyFunctionList(ctx, glfw_window_proto, glfw_window_proto_trigfuncs, countof(glfw_window_proto_trigfuncs));
  JS_SetPropertyFunctionList(ctx, glfw_window_proto, glfw_window_proto_handlers, countof(glfw_window_proto_handlers));
  JS_SetClassProto(ctx, glfw_window_class_id, glfw_window_proto);

  glfw_window_class = JS_NewCFunction2(ctx, glfw_window_constructor, "Window", 5, JS_CFUNC_constructor, 0);
  JS_SetPropertyFunctionList(ctx, glfw_window_class, glfw_window_funcs, countof(glfw_window_funcs));
  JS_SetConstructor(ctx, glfw_window_class, glfw_window_proto);

  JS_SetModuleExport(ctx, m, "Window", glfw_window_class);

  return 0;
}

int
glfw_window_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Window");
}
