cmake_minimum_required(VERSION 3.23)

project(platypus)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(platypus ${HEADERS} ${SOURCES})
target_compile_features(platypus PRIVATE cxx_std_17)

if(EMSCRIPTEN)
    set_target_properties(platypus PROPERTIES LINK_FLAGS "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap")
endif()

# after build copy index.html into the build folder
configure_file(
    ${CMAKE_SOURCE_DIR}/html/index.html
    ${CMAKE_BINARY_DIR}
    COPYONLY)
