cmake_minimum_required(VERSION 3.22)

set(HEADERS
    src/canvas.h
    src/engine.h
)

set(SOURCES
    src/engine.cpp
    src/main.cpp
)

project(platypus)
add_executable(platypus ${HEADERS} ${SOURCES})
target_compile_features(platypus PRIVATE cxx_std_17)

if(EMSCRIPTEN)
    set_target_properties(platypus PROPERTIES LINK_FLAGS "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap -sUSE_GLFW=3")
    target_link_libraries(platypus glfw3)
else()
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    target_link_libraries(platypus glfw GL)
endif()

# after build copy index.html into the build folder
configure_file(
    ${CMAKE_SOURCE_DIR}/html/index.html
    ${CMAKE_BINARY_DIR}
    COPYONLY)
