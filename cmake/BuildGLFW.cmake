macro(build_glfw SOURCE BINARY SUFFIX PIC)
  include(ExternalProject)

  # GLFW's source (the vendored submodule) is shared between the shared- and
  # static-module builds, so cloning/patching it must happen exactly once -
  # doing it once per variant races two ExternalProject download steps against
  # the same directory.
  if(NOT TARGET glfw_source)
    # GLFW's own src/CMakeLists.txt hardcodes POSITION_INDEPENDENT_CODE ON on its
    # "glfw" target, so -DCMAKE_POSITION_INDEPENDENT_CODE has no effect on it; replace
    # the hardcoded ON with a variable so each variant below can control it via
    # -DGLFW_FORCE_PIC instead.
    ExternalProject_Add(
      glfw_source
      SOURCE_DIR ${SOURCE}/glfw
      GIT_REPOSITORY https://github.com/glfw/glfw.git
      UPDATE_COMMAND sed -i "s|DEFINE_SYMBOL _GLFW_BUILD_DLL||g;s|POSITION_INDEPENDENT_CODE ON|POSITION_INDEPENDENT_CODE \${GLFW_FORCE_PIC}|" ${SOURCE}/glfw/src/CMakeLists.txt
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ""
      USES_TERMINAL_DOWNLOAD ON)
  endif(NOT TARGET glfw_source)

  message("-- Building GLFW from source (${SUFFIX}, PIC=${PIC})")

  ExternalProject_Add(
    glfw_${SUFFIX}
    SOURCE_DIR ${SOURCE}/glfw
    BINARY_DIR ${BINARY}/glfw-${SUFFIX}
    DOWNLOAD_COMMAND ""
    UPDATE_COMMAND ""
    DEPENDS glfw_source
    PREFIX glfw-${SUFFIX}
    CMAKE_ARGS -DBUILD_SHARED_LIBS:BOOL=OFF -DENABLE_SHARED:BOOL=OFF "-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}" "-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=${PIC}" "-DGLFW_FORCE_PIC:BOOL=${PIC}" "-DCMAKE_C_COMPILER:STRING=${CMAKE_C_COMPILER}" "-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS} ${MODULE_COMPILE_FLAGS}" -DGLFW_BUILD_DOCS:BOOL=OFF -DGLFW_BUILD_EXAMPLES:BOOL=OFF -DGLFW_BUILD_TESTS:BOOL=OFF
    CMAKE_GENERATOR ${CMAKE_GENERATOR}
    CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
    INSTALL_COMMAND ""
    #[[LOG_DOWNLOAD ON
    LOG_BUILD ON]]
    LOG_CONFIGURE ON
    # USES_TERMINAL_CONFIGURE OFF
    USES_TERMINAL_BUILD ON)

  ExternalProject_Get_Property(glfw_${SUFFIX} SOURCE_DIR BINARY_DIR)

  add_library(glfw3_${SUFFIX} STATIC IMPORTED GLOBAL)

  add_dependencies(glfw3_${SUFFIX} glfw_${SUFFIX})

  if(MSVC)
    set_target_properties(glfw3_${SUFFIX} PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/src/glfw.lib)
  else()
    set_target_properties(glfw3_${SUFFIX} PROPERTIES IMPORTED_LOCATION ${BINARY_DIR}/src/libglfw3.a)

  endif()

  set(GLFW_INCLUDE_DIR ${SOURCE_DIR}/include CACHE PATH "glfw3 include directory" FORCE)
  set(GLFW_LIBRARY_DIR_${SUFFIX} ${BINARY_DIR}/src CACHE PATH "glfw3 ${SUFFIX} library directory" FORCE)
  set(GLFW_LIBRARY_${SUFFIX} glfw3_${SUFFIX})
endmacro(build_glfw)
