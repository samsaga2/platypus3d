cmake_minimum_required(VERSION 3.22)

set(HEADERS
    src/util.h
    src/shader.h
    src/mesh.h
    src/engine.h
)

set(SOURCES
    src/util.cpp
    src/engine.cpp
    src/shader.cpp
    src/mesh.cpp
    src/main.cpp
)

project(platypus)
add_executable(platypus ${HEADERS} ${SOURCES})
target_compile_features(platypus PRIVATE cxx_std_17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(platypus glfw GL)
target_compile_definitions(platypus PUBLIC GL_GLEXT_PROTOTYPES)

# copy compile commands after build
add_custom_target(
  copy-compile-commands ALL
  ${CMAKE_COMMAND} -E copy_if_different
  ${CMAKE_BINARY_DIR}/compile_commands.json
  ${CMAKE_CURRENT_LIST_DIR})
