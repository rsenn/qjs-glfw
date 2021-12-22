project(qjs-glfw C)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQuickJS.cmake)
# include(FindGLEW)
include(FindPkgConfig)
include(CheckFunctionExists)

pkg_search_module(GLEW glew)
pkg_search_module(GLFW glfw3)

set(GLEW_LIBRARY "${pkgcfg_lib_GLEW_glew32}")
set(GLFW_LIBRARY "${pkgcfg_lib_GLFW_glfw3}")
message(STATUS "GLEW_LIBRARY: ${GLEW_LIBRARY}")
message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")

find_quickjs()

if(WIN32)
  add_definitions(-DGLFW_DLL)
endif(WIN32)

list(APPEND CMAKE_REQUIRED_INCLUDES ${GLFW_INCLUDE_DIRS})
list(APPEND CMAKE_REQUIRED_LIBRARIES ${GLFW_LIBRARIES})

check_function_exists(glfwGetError GLFW_GET_ERROR)
if(GLFW_GET_ERROR)
  add_definitions(-DHAVE_GLFW_GET_ERROR=1)
endif(GLFW_GET_ERROR)

check_function_exists(glfwGetMonitorContentScale GLFW_GET_MONITOR_CONTENT_SCALE)
if(GLFW_GET_MONITOR_CONTENT_SCALE)
  add_definitions(-DHAVE_GLFW_GET_MONITOR_CONTENT_SCALE=1)
endif(GLFW_GET_MONITOR_CONTENT_SCALE)

check_function_exists(glfwGetMonitorWorkarea GLFW_GET_MONITOR_WORKAREA)
if(GLFW_GET_MONITOR_WORKAREA)
  add_definitions(-DHAVE_GLFW_GET_MONITOR_WORKAREA=1)
endif(GLFW_GET_MONITOR_WORKAREA)

check_function_exists(glfwWindowHintString GLFW_WINDOW_HINT_STRING)
if(GLFW_WINDOW_HINT_STRING)
  add_definitions(-DHAVE_GLFW_WINDOW_HINT_STRING=1)
endif(GLFW_WINDOW_HINT_STRING)

check_function_exists(glfwSetWindowOpacity GLFW_SET_WINDOW_OPACITY)
if(GLFW_SET_WINDOW_OPACITY)
  add_definitions(-DHAVE_GLFW_SET_WINDOW_OPACITY=1)
endif(GLFW_SET_WINDOW_OPACITY)

check_function_exists(glfwGetWindowOpacity GLFW_GET_WINDOW_OPACITY)
if(GLFW_GET_WINDOW_OPACITY)
  add_definitions(-DHAVE_GLFW_GET_WINDOW_OPACITY=1)
endif(GLFW_GET_WINDOW_OPACITY)

check_function_exists(glfwSetWindowMaximizeCallback GLFW_SET_WINDOW_MAXIMIZE_CALLBACK)
if(GLFW_SET_WINDOW_MAXIMIZE_CALLBACK)
  add_definitions(-DHAVE_GLFW_SET_WINDOW_MAXIMIZE_CALLBACK=1)
endif(GLFW_SET_WINDOW_MAXIMIZE_CALLBACK)

check_function_exists(glfwSetWindowContentScaleCallback GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK)
if(GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK)
  add_definitions(-DHAVE_GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK=1)
endif(GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK)

check_function_exists(glfwRequestWindowAttention GLFW_REQUEST_WINDOW_ATTENTION)
if(GLFW_REQUEST_WINDOW_ATTENTION)
  add_definitions(-DHAVE_GLFW_REQUEST_WINDOW_ATTENTION=1)
endif(GLFW_REQUEST_WINDOW_ATTENTION)



add_library(qjs-glfw SHARED gamma_ramp.c gamma_ramp.h glfw.c glfw.h monitor.c monitor.h position.c position.h scale.c scale.h size.c size.h video_mode.c video_mode.h window.c window.h workarea.c workarea.h)

set_target_properties(qjs-glfw PROPERTIES OUTPUT_NAME glfw PREFIX "")

target_include_directories(qjs-glfw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src)
target_link_libraries(qjs-glfw PRIVATE ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${QUICKJS_LIBRARY})
target_compile_definitions(qjs-glfw PRIVATE JS_SHARED_LIBRARY=1)
install(TARGETS qjs-glfw DESTINATION lib/quickjs PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
