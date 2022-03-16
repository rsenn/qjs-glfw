macro(build_glfw)
  message("-- Building GLFW from source")

  include(ExternalProject)

  ExternalProject_Add(
    glfw3
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    PREFIX glfw
    CMAKE_ARGS
      -DBUILD_SHARED_LIBS:BOOL=OFF
      "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}"
      "-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=${CMAKE_POSITION_INDEPENDENT_CODE}"
      "-DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}"
      "-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}"
    CMAKE_GENERATOR ${CMAKE_GENERATOR}
    CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    USES_TERMINAL_DOWNLOAD ON
    USES_TERMINAL_CONFIGURE ON
    USES_TERMINAL_BUILD ON)

  ExternalProject_Get_Property(glfw3 SOURCE_DIR BINARY_DIR)

  add_library(glfw STATIC IMPORTED GLOBAL)

  add_dependencies(glfw glfw3)

  if(MSVC)
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION
                                          ${BINARY_DIR}/src/glfw3.lib)
  else()
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION
                                          ${BINARY_DIR}/src/libglfw3.a)

  endif()

  set(GLFW_INCLUDE_DIR ${SOURCE_DIR}/c/include
      CACHE PATH "glfw include directory" FORCE)
  set(GLFW_LIBRARY_DIR ${BINARY_DIR} CACHE PATH "glfw include directory" FORCE)
  set(GLFW_LIBRARY glfw)
endmacro(build_glfw)
