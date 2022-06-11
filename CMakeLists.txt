cmake_minimum_required(VERSION 3.22)

set(HEADERS
    src/camera.h
    src/engine.h
    src/material.h
    src/mesh.h
    src/model.h
    src/model_loader.h
    src/point_light.h
    src/shader.h
    src/stb_image.h
    src/texture.h
    src/transform.h
    src/uniform_block.h
    src/util.h
    src/vertex_format.h
    src/vertex_buffer.h
)

set(SOURCES
    src/camera.cpp
    src/engine.cpp
    src/main.cpp
    src/material.cpp
    src/mesh.cpp
    src/model.cpp
    src/model_loader.cpp
    src/render_device.cpp
    src/shader.cpp
    src/texture.cpp
    src/uniform_block.cpp
    src/util.cpp
    src/vertex_format.cpp
    src/vertex_buffer.cpp
)

project(platypus)
add_executable(platypus ${HEADERS} ${SOURCES})
target_compile_features(platypus PRIVATE cxx_std_17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(platypus glfw GL assimp)
target_compile_definitions(platypus PUBLIC GL_GLEXT_PROTOTYPES)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif()

add_custom_target(
  copy-compile-commands ALL
  ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json
  ${CMAKE_CURRENT_LIST_DIR})
