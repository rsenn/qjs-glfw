macro(build_gl3w)
  message("-- Building gl3w from source")

  include(ExternalProject)

  ExternalProject_Add(
    gl3w
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gl3w
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gl3w
    GIT_REPOSITORY https://github.com/skaslev/gl3w.git
    PATCH_COMMAND patch -p1 -N -i ${CMAKE_CURRENT_SOURCE_DIR}/gl3w-cmake.patch
    PREFIX gl3w
    CMAKE_ARGS
      -DBUILD_SHARED_LIBS:BOOL=OFF
      "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
      "-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=${CMAKE_POSITION_INDEPENDENT_CODE}"
      "-DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}"
      "-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS} ${MODULE_COMPILE_FLAGS}"
      -DGL3W_BUILD_DOCS:BOOL=OFF
      -DGL3W_BUILD_EXAMPLES:BOOL=OFF
      -DGL3W_BUILD_TESTS:BOOL=ON
    CMAKE_GENERATOR ${CMAKE_GENERATOR}
    CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
    # INSTALL_COMMAND ""
    USES_TERMINAL_DOWNLOAD ON
    LOG_CONFIGURE ON
    USES_TERMINAL_BUILD ON)

  ExternalProject_Get_Property(gl3w SOURCE_DIR BINARY_DIR)
  dump(SOURCE_DIR BINARY_DIR)

  # add_dependencies(${BINARY_DIR}/src/gl3w.c gl3w)
  add_library(libgl3w STATIC IMPORTED)
  add_dependencies(libgl3w gl3w)

  if(MSVC)
    set_target_properties(
      libgl3w PROPERTIES IMPORTED_LOCATION
                         ${CMAKE_CURRENT_BINARY_DIR}/gl3w/src/gl3w.lib)
  else()
    set_target_properties(
      libgl3w PROPERTIES IMPORTED_LOCATION
                         ${CMAKE_CURRENT_BINARY_DIR}/gl3w/src/libgl3w.a)

  endif()

  get_target_property(GL3W_LIBRARY_FILE libgl3w IMPORTED_LOCATION)
  dump(GL3W_LIBRARY_FILE)

  set(GL3W_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/gl3w/include"
      CACHE PATH "gl3w include directory")
  set(GL3W_LIBRARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/gl3w/src"
      CACHE PATH "gl3w library directory")
  set(GL3W_LIBRARY "${GL3W_LIBRARY_FILE}" CACHE STRING "gl3w library")

  #[[  if(NOT GL3W_SOURCE)
    if(EXISTS ${BINARY_DIR}/src/gl3w.c)
      set(GL3W_SOURCE ${BINARY_DIR}/src/gl3w.c CACHE PATH "gl3w source" FORCE)
    endif()
  endif()

  set(GL3W_SOURCE "${GL3W_SOURCE}" CACHE PATH "gl3w source")]]

endmacro(build_gl3w)
