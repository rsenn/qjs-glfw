# quickjs_module_options([SHARED_DEFAULT <ON|OFF>] [STATIC_DEFAULT <ON|OFF>])
#
# Declares BUILD_SHARED_MODULES/BUILD_STATIC_MODULES the same way across
# every qjs-* project, so a single -DBUILD_SHARED_MODULES=.../
# -DBUILD_STATIC_MODULES=... passed to the top-level quickjs/ build reaches
# every add_subdirectory()'d qjs-* submodule unchanged (same cache-variable
# name everywhere). Guarded by NOT DEFINED so a value already set by the
# caller - this project's own earlier option() call, or the outer build -
# always wins; this macro only ever supplies the fallback default.
#
# WASI/Emscripten have no dlopen()-able shared-module story, so the shared
# default is forced off and the static default forced on there regardless
# of what the caller asked for.
macro(quickjs_module_options)
  cmake_parse_arguments(QMO "" "SHARED_DEFAULT;STATIC_DEFAULT" "" ${ARGN})
  if(NOT DEFINED QMO_SHARED_DEFAULT)
    set(QMO_SHARED_DEFAULT ON)
  endif(NOT DEFINED QMO_SHARED_DEFAULT)
  if(NOT DEFINED QMO_STATIC_DEFAULT)
    set(QMO_STATIC_DEFAULT OFF)
  endif(NOT DEFINED QMO_STATIC_DEFAULT)

  if(WASI OR EMSCRIPTEN OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    set(QMO_SHARED_DEFAULT OFF)
    set(QMO_STATIC_DEFAULT ON)
  endif(WASI OR EMSCRIPTEN OR "${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")

  if(NOT DEFINED BUILD_SHARED_MODULES)
    option(BUILD_SHARED_MODULES "Build shared QuickJS module(s) (*.so)" ${QMO_SHARED_DEFAULT})
  endif(NOT DEFINED BUILD_SHARED_MODULES)
  if(NOT DEFINED BUILD_STATIC_MODULES)
    option(BUILD_STATIC_MODULES "Build static QuickJS module(s) (*.a)" ${QMO_STATIC_DEFAULT})
  endif(NOT DEFINED BUILD_STATIC_MODULES)
endmacro(quickjs_module_options)
