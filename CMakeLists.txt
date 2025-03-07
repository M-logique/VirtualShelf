cmake_minimum_required(VERSION 3.10)
project(VirtualShelf)

set(CMAKE_CXX_STANDARD 14)

set(GO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libtui)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/VSinclude)

file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB GO_FILES ${GO_SOURCE_DIR}/*.go)

add_executable(VirtualShelf main.cpp ${SRC_FILES})

if(WIN32)
    # Windows-specific options
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/libtui.a
        COMMAND go build -buildmode=c-archive -o ${CMAKE_BINARY_DIR}/libtui.a ${GO_FILES}
        WORKING_DIRECTORY ${GO_SOURCE_DIR}
        COMMENT "Building Go project as a static library (Windows)"
    )

    target_link_libraries(VirtualShelf msvcrt.lib legacy_stdio_definitions.lib)

elseif(UNIX)
    # Linux-specific options
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/libtui.a
        COMMAND go build -buildmode=c-archive -o ${CMAKE_BINARY_DIR}/libtui.a ${GO_FILES}
        WORKING_DIRECTORY ${GO_SOURCE_DIR}
        COMMENT "Building Go project as a static library (Linux)"
    )
endif()

add_custom_target(BuildLibtui ALL DEPENDS ${CMAKE_BINARY_DIR}/libtui.a)
target_link_libraries(VirtualShelf ${CMAKE_BINARY_DIR}/libtui.a)

add_dependencies(VirtualShelf BuildLibtui)