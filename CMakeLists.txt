cmake_minimum_required(VERSION 3.22)

set(HEADERS
    src/shader.h
    src/model.h
    src/engine.h
)

set(SOURCES
    src/engine.cpp
    src/shader.cpp
    src/model.cpp
    src/main.cpp
)

project(platypus)
add_executable(platypus ${HEADERS} ${SOURCES})
target_compile_features(platypus PRIVATE cxx_std_17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(platypus glfw GL)
target_compile_definitions(platypus PUBLIC GL_GLEXT_PROTOTYPES)
