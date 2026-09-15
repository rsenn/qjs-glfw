cmake_minimum_required(VERSION 3.23)

project(qjs-glfw VERSION 0.9 LANGUAGES C)

message("Building project [1;31m${PROJECT_NAME}[0m")

set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH TRUE)

option(BUILD_GLFW OFF "Build GLFW from sources")
option(USE_GL3W OFF "Use GL3W instead of GLEW")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/QuickJSModule.cmake)
quickjs_module_options(SHARED_DEFAULT ON STATIC_DEFAULT ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/check-flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindQuickJS.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UseMultiArch.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLEW.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLFW.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGLFW.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindMarkdown.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/markdown.cmake)

if(USE_GL3W)
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildGL3W.cmake)
endif(USE_GL3W)

check_flag("-fvisibility=hidden" VISIBILITY_HIDDEN MODULE_COMPILE_FLAGS)

# dump(MODULE_COMPILE_FLAGS)

find_quickjs()
configure_quickjs()

find_glew()

if(BUILD_GLFW)
  # GLFW is a static lib linked into both qjs-glfw (a .so) and qjs-glfw-static (a .a
  # meant for linking into another executable), so it must be built twice: with -fPIC
  # for the shared module, without for the static one.
  if(BUILD_SHARED_MODULES)
    build_glfw(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} shared ON)
  endif(BUILD_SHARED_MODULES)
  if(BUILD_STATIC_MODULES)
    build_glfw(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} static OFF)
  endif(BUILD_STATIC_MODULES)

  add_definitions(-DHAVE_GLFW_GET_ERROR -DHAVE_GLFW_GET_MONITOR_CONTENT_SCALE -DHAVE_GLFW_GET_MONITOR_WORKAREA -DHAVE_GLFW_GET_WINDOW_OPACITY -DHAVE_GLFW_REQUEST_WINDOW_ATTENTION -DHAVE_GLFW_SET_WINDOW_CONTENT_SCALE_CALLBACK -DHAVE_GLFW_SET_WINDOW_MAXIMIZE_CALLBACK -DHAVE_GLFW_SET_WINDOW_OPACITY -DHAVE_GLFW_WINDOW_HINT_STRING)
else(BUILD_GLFW)
  find_glfw()
  set(GLFW_LIBRARY_DIR_shared ${GLFW_LIBRARY_DIR})
  set(GLFW_LIBRARY_shared ${GLFW_LIBRARY})
  set(GLFW_LIBRARY_DIR_static ${GLFW_LIBRARY_DIR})
  set(GLFW_LIBRARY_static ${GLFW_LIBRARY})
endif(BUILD_GLFW)

if(USE_GL3W)

  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include/GL)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include/KHR)
  file(DOWNLOAD "https://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h" ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include/GL/glcorearb.h SHOW_PROGRESS)
  file(DOWNLOAD "https://www.khronos.org/registry/EGL/api/KHR/khrplatform.h" ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include/KHR/khrplatform.h SHOW_PROGRESS)

  build_gl3w()

  include_directories(${CMAKE_CURRENT_BINARY_DIR}/gl3w/include)
  add_definitions(-DUSE_GL3W)
  set(GL3W_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/gl3w/src/gl3w.c)
endif(USE_GL3W)

# message(STATUS "GL3W_INCLUDE_DIR: ${GL3W_INCLUDE_DIR}") message(STATUS "GL3W_LIBRARY: ${GL3W_LIBRARY}") message(STATUS "GLFW_INCLUDE_DIR: ${GLFW_INCLUDE_DIR}") message(STATUS "GLFW_LIBRARY: ${GLFW_LIBRARY}")

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/gl3w/include ${GL3W_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${QUICKJS_INCLUDE_DIR})
link_directories(${GL3W_LIBRARY_DIR} ${GLFW_LIBRARY_DIR_shared} ${GLFW_LIBRARY_DIR_static} ${QUICKJS_LIBRARY_DIR})

if(WIN32)
  add_definitions(-DGLFW_DLL)
endif(WIN32)

if(NOT BUILD_GLFW)
  include(CheckFunctionExists)
  include(CheckLibraryExists)

  list(APPEND CMAKE_REQUIRED_INCLUDES ${GLFW_INCLUDE_DIR} ${GL3W_INCLUDE_DIR})
  list(APPEND CMAKE_REQUIRED_LIBRARIES ${GLFW_LIBRARY} ${GL3W_LIBRARY})

  check_function_exists(glfwGetPlatform GLFW_GET_PLATFORM)
  if(GLFW_GET_PLATFORM)
    add_definitions(-DHAVE_GLFW_GET_PLATFORM=1)
  endif(GLFW_GET_PLATFORM)

  check_function_exists(glfwPlatformSupported GLFW_PLATFORM_SUPPORTED)
  if(GLFW_PLATFORM_SUPPORTED)
    add_definitions(-DHAVE_GLFW_PLATFORM_SUPPORTED=1)
  endif(GLFW_PLATFORM_SUPPORTED)

  check_function_exists(glfwGetError GLFW_GET_ERROR)
  if(GLFW_GET_ERROR)
    add_definitions(-DHAVE_GLFW_GET_ERROR=1)
  endif(GLFW_GET_ERROR)

  check_function_exists(glfwGetMonitorContentScale GLFW_GET_MONITOR_CONTENT_SCALE)
  if(GLFW_GET_MONITOR_CONTENT_SCALE)
    add_definitions(-DHAVE_GLFW_GET_MONITOR_CONTENT_SCALE=1)
  endif(GLFW_GET_MONITOR_CONTENT_SCALE)

  check_function_exists(glfwGetMonitorWorkarea GLFW_GET_MONITOR_WORKAREA)
  if(NOT GLFW_GET_MONITOR_WORKAREA)
    check_library_exists("${GLFW_LIBRARY}" glfwGetMonitorWorkarea "" GLFW_GET_MONITOR_WORKAREA)
  endif(NOT GLFW_GET_MONITOR_WORKAREA)

  if(GLFW_GET_MONITOR_WORKAREA)
    add_definitions(-DHAVE_GLFW_GET_MONITOR_WORKAREA=1)
  endif(GLFW_GET_MONITOR_WORKAREA)
  # message("GLFW_GET_MONITOR_WORKAREA: ${GLFW_GET_MONITOR_WORKAREA}")

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
endif(NOT BUILD_GLFW)

# ${CMAKE_CURRENT_BINARY_DIR}/gl3w/src/gl3w.c
set(QJS_GLFW_SOURCES gamma_ramp.c gamma_ramp.h glfw.c glfw.h image.c image.h monitor.c monitor.h position.c position.h scale.c scale.h size.c size.h video_mode.c video_mode.h window.c window.h workarea.c workarea.h)

if(USE_GL3W)
  list(APPEND IMGUI_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/gl3w/src/gl3w.c)
endif(USE_GL3W)

link_directories(${GL3W_LIBRARY_DIR} ${GLEW_LIBRARY_DIR} ${GLFW_LIBRARY_DIR_shared} ${GLFW_LIBRARY_DIR_static})

if(BUILD_SHARED_MODULES)
  add_library(qjs-glfw SHARED ${QJS_GLFW_SOURCES} ${GL3W_SOURCE})

  #[[if(USE_GL3W)
    add_dependencies(qjs-glfw gl3w_gen)
  endif(USE_GL3W)]]

  set_target_properties(qjs-glfw PROPERTIES OUTPUT_NAME glfw PREFIX "" # COMPILE_FLAGS "${MODULE_COMPILE_FLAGS}"
  )

  target_compile_options(qjs-glfw PRIVATE ${MODULE_COMPILE_FLAGS})

  target_include_directories(qjs-glfw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src)

  # dump(GL3W_LIBRARY_DIR)

  target_link_libraries(qjs-glfw PRIVATE ${GL3W_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY_shared} ${QUICKJS_LIBRARY})
  target_compile_definitions(qjs-glfw PRIVATE JS_SHARED_LIBRARY=1)

  if(NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
  endif(NOT CMAKE_INSTALL_LIBDIR)
  if(NOT QUICKJS_C_MODULE_DIR)
    set(QUICKJS_C_MODULE_DIR "${CMAKE_INSTALL_LIBDIR}/quickjs")
  endif(NOT QUICKJS_C_MODULE_DIR)

  install(TARGETS qjs-glfw DESTINATION "${QUICKJS_C_MODULE_DIR}" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endif(BUILD_SHARED_MODULES)

# Static counterpart for embedders that want glfw linked directly into their own
# interpreter binary (e.g. qjsm's EXTERNAL_MODULES) instead of dlopen'd at runtime.
# Without JS_SHARED_LIBRARY, glfw.h's js_init_module macro expands to
# js_init_module_glfw, matching the js_init_module_<name> convention EXTERNAL_MODULES
# expects.
if(BUILD_STATIC_MODULES)
  add_library(qjs-glfw-static STATIC ${QJS_GLFW_SOURCES} ${GL3W_SOURCE})
  set_target_properties(qjs-glfw-static PROPERTIES
    PREFIX "" OUTPUT_NAME "quickjs-glfw" SUFFIX ".a"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    POSITION_INDEPENDENT_CODE OFF)
  target_compile_options(qjs-glfw-static PRIVATE ${MODULE_COMPILE_FLAGS})
  target_include_directories(qjs-glfw-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src)
  target_link_libraries(qjs-glfw-static PUBLIC ${GL3W_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY_static} ${QUICKJS_LIBRARY})

  # Sidecar for a different top-level project's CMakeLists.txt to include() and pick up
  # this archive's transitive link dependencies, which a plain .a carries no record of.
  set(QUICKJS_GLFW_LIBRARIES ${GL3W_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY_static} ${QUICKJS_LIBRARY})
  set(QUICKJS_GLFW_LINK_FLAGS "")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/quickjs-glfw.cmake" "\
set(QUICKJS_GLFW_LIBRARIES \"${QUICKJS_GLFW_LIBRARIES}\")
set(QUICKJS_GLFW_LINK_FLAGS \"${QUICKJS_GLFW_LINK_FLAGS}\")
")
endif(BUILD_STATIC_MODULES)

# include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/pandoc-helper.cmake)

file(GLOB MARKDOWN_DOCS doc/*.md)
md2html(${MARKDOWN_DOCS})
