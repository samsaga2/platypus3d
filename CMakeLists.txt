cmake_minimum_required(VERSION 3.22)

set(HEADERS
    src/util.h
    src/stb_image.h

    src/shader.h
    src/texture.h
    src/material.h
    src/vertex_buffer.h
    src/render_device.h
    src/render_factory.h

    src/gl_texture.h
    src/gl_shader.h
    src/gl_vertex_buffer.h
    src/gl_indexed_vertex_buffer.h
    src/gl_render_factory.h

    src/transform.h
    src/camera.h
    src/engine.h
)

set(SOURCES
    src/util.cpp

    src/engine.cpp
    src/material.cpp

    src/gl_shader.cpp
    src/gl_texture.cpp
    src/gl_vertex_buffer.cpp
    src/gl_indexed_vertex_buffer.cpp
    src/gl_render_device.cpp
    src/gl_render_factory.cpp

    src/camera.cpp
    src/main.cpp
)

project(platypus)
add_executable(platypus ${HEADERS} ${SOURCES})
target_compile_features(platypus PRIVATE cxx_std_17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(platypus glfw GL)
target_compile_definitions(platypus PUBLIC GL_GLEXT_PROTOTYPES)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

add_custom_target(
  copy-compile-commands ALL
  ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json
  ${CMAKE_CURRENT_LIST_DIR})
