#include "glfw.h"
#include "video_mode.h"
#include "gamma_ramp.h"
#include "monitor.h"
#include "workarea.h"

JSClassID glfw_monitor_class_id = 0;
JSValue glfw_monitor_proto, glfw_monitor_class;

// constructor/destructor
static JSValue
glfw_monitor_constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst argv[]) {
  GLFWmonitor* monitor;

  if((monitor = glfwGetPrimaryMonitor()))
    return glfw_monitor_wrap(ctx, monitor);

  return JS_UNDEFINED;
}

// properties
static JSValue
glfw_monitor_get_name(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  const char* name;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  if((name = glfwGetMonitorName(monitor)))
    return JS_NewString(ctx, name);

  return JS_UNDEFINED;
}

static JSValue
glfw_monitor_get_position(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  int x, y;
  GLFWposition pos;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  glfwGetMonitorPos(monitor, &pos.x, &pos.y);

  return glfw_position_write(ctx, pos);
}

static JSValue
glfw_monitor_get_workarea(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  GLFWworkarea workarea;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

#ifdef HAVE_GLFW_GET_MONITOR_WORKAREA
  glfwGetMonitorWorkarea(
      monitor, &workarea.position.x, &workarea.position.y, &workarea.size.width, &workarea.size.height);
#endif

  return glfw_workarea_write(ctx, workarea);
}

static JSValue
glfw_monitor_get_physical_size(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  GLFWsize size;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  glfwGetMonitorPhysicalSize(monitor, &size.width, &size.height);
  return glfw_size_write(ctx, size);
}

static JSValue
glfw_monitor_get_content_scale(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  GLFWposition_f scale;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

#ifdef HAVE_GLFW_GET_MONITOR_CONTENT_SCALE
  glfwGetMonitorContentScale(monitor, &scale.x, &scale.y);
#endif
  return glfw_position_f_write(ctx, scale);
}

static JSValue
glfw_monitor_get_current_video_mode(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  const GLFWvidmode* video_mode;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  if((video_mode = glfwGetVideoMode(monitor)))
    return glfw_video_mode_wrap(ctx, *video_mode);

  return JS_UNDEFINED;
}

static JSValue
glfw_monitor_get_video_modes(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  const GLFWvidmode* video_modes;
  int count;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  video_modes = glfwGetVideoModes(monitor, &count);

  JSValue array = JS_NewArray(ctx);

  for(int i = 0; i < count; i++) {
    JSValue video_mode = glfw_video_mode_wrap(ctx, video_modes[i]);
    JS_SetPropertyInt64(ctx, array, i, video_mode);
  }

  return array;
}

static JSValue
glfw_monitor_get_gamma(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;
  const GLFWgammaramp* gamma;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  if((gamma = glfwGetGammaRamp(monitor)))
    return glfw_gamma_ramp_wrap(ctx, gamma);

  return JS_UNDEFINED;
}

static JSValue
glfw_monitor_set_gamma(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWmonitor* monitor;
  GLFWgammaramp* gamma_ramp;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  if(JS_IsNumber(value)) {
    float gamma = JS_VALUE_GET_FLOAT64(value);
    glfwSetGamma(monitor, gamma);
    return JS_UNDEFINED;
  } else if(!(gamma_ramp = JS_GetOpaque2(ctx, value, glfw_gamma_ramp_class_id)))
    return JS_EXCEPTION;

  glfwSetGammaRamp(monitor, gamma_ramp);

  return JS_UNDEFINED;
}

// Static properties
static JSValue
glfw_monitor_get_monitors(JSContext* ctx, JSValueConst this_val) {
  int count;
  GLFWmonitor** monitors = glfwGetMonitors(&count);

  JSValue array = JS_NewArray(ctx);
  for(int i = 0; i < count; i++) {
    JSValue monitor = glfw_monitor_wrap(ctx, monitors[i]);
    JS_SetPropertyInt64(ctx, array, i, monitor);
  }

  return array;
}

static JSValue
glfw_monitor_get_ptr(JSContext* ctx, JSValueConst this_val) {
  GLFWmonitor* monitor;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  return js_newptr(ctx, glfwGetMonitorUserPointer(monitor));
}

static JSValue
glfw_monitor_set_ptr(JSContext* ctx, JSValueConst this_val, JSValueConst value) {
  GLFWmonitor* monitor;

  if(!(monitor = JS_GetOpaque2(ctx, this_val, glfw_monitor_class_id)))
    return JS_EXCEPTION;

  glfwSetMonitorUserPointer(monitor, js_getptr(ctx, value));
  return JS_UNDEFINED;
}

// initialization
static JSClassDef glfw_monitor_class_def = {
    .class_name = "Monitor",
};

static const JSCFunctionListEntry glfw_monitor_proto_funcs[] = {
    JS_CGETSET_ENUMERABLE_DEF("name", glfw_monitor_get_name, NULL),
    JS_CGETSET_DEF("position", glfw_monitor_get_position, NULL),
    JS_CGETSET_DEF("workarea", glfw_monitor_get_workarea, NULL),
    JS_CGETSET_DEF("physicalSize", glfw_monitor_get_physical_size, NULL),
    JS_CGETSET_DEF("contentScale", glfw_monitor_get_content_scale, NULL),
    JS_CGETSET_DEF("currentVideoMode", glfw_monitor_get_current_video_mode, NULL),
    JS_CGETSET_DEF("videoModes", glfw_monitor_get_video_modes, NULL),
    JS_CGETSET_DEF("gamma", glfw_monitor_get_gamma, glfw_monitor_set_gamma),
    JS_CGETSET_DEF("userPointer", glfw_monitor_get_ptr, glfw_monitor_set_ptr),
    JS_PROP_STRING_DEF("[Symbol.toStringTag]", "GLFWmonitor", JS_PROP_CONFIGURABLE),
};

static const JSCFunctionListEntry glfw_monitor_funcs[] = {
    JS_CGETSET_DEF("monitors", glfw_monitor_get_monitors, NULL),
};

int
glfw_monitor_init(JSContext* ctx, JSModuleDef* m) {
  JS_NewClassID(&glfw_monitor_class_id);
  JS_NewClass(JS_GetRuntime(ctx), glfw_monitor_class_id, &glfw_monitor_class_def);

  glfw_monitor_proto = JS_NewObject(ctx);
  JS_SetPropertyFunctionList(ctx, glfw_monitor_proto, glfw_monitor_proto_funcs, countof(glfw_monitor_proto_funcs));
  JS_SetClassProto(ctx, glfw_monitor_class_id, glfw_monitor_proto);

  glfw_monitor_class = JS_NewCFunction2(ctx, glfw_monitor_constructor, "Monitor", 5, JS_CFUNC_constructor, 0);
  JS_SetPropertyFunctionList(ctx, glfw_monitor_class, glfw_monitor_funcs, countof(glfw_monitor_funcs));
  JS_SetConstructor(ctx, glfw_monitor_class, glfw_monitor_proto);
  JS_SetModuleExport(ctx, m, "Monitor", glfw_monitor_class);
  return 0;
}

JSValue
glfw_monitor_wrap(JSContext* ctx, GLFWmonitor* monitor) {
  JSValue proto = JS_GetPropertyStr(ctx, glfw_monitor_class, "prototype");
  if(JS_IsException(proto)) {
    JS_FreeValue(ctx, proto);
    return JS_EXCEPTION;
  }

  JSValue obj = JS_NewObjectProtoClass(ctx, proto, glfw_monitor_class_id);
  JS_FreeValue(ctx, proto);
  if(JS_IsException(obj)) {
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
  }

  JS_SetOpaque(obj, monitor);
  return obj;
}

int
glfw_monitor_export(JSContext* ctx, JSModuleDef* m) {
  return JS_AddModuleExport(ctx, m, "Monitor");
}
