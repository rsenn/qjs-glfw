project(qjs-glfw C)

add_library(
  qjs-glfw SHARED
  gamma_ramp.c gamma_ramp.h glfw.c glfw.h monitor.c monitor.h position.c position.h scale.c scale.h
  size.c size.h video_mode.c video_mode.h window.c window.h workarea.c workarea.h)

set_target_properties(qjs-glfw PROPERTIES OUTPUT_NAME glfw PREFIX "")

target_include_directories(qjs-glfw PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src)
target_link_libraries(qjs-glfw PRIVATE GLEW glfw)
target_compile_definitions(qjs-glfw PRIVATE JS_SHARED_LIBRARY=1)
install(TARGETS qjs-glfw DESTINATION lib/quickjs
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ
                    WORLD_EXECUTE)
