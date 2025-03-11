cmake_minimum_required(VERSION 3.10)
project(VirtualShelf)

set(CMAKE_CXX_STANDARD 14)

set(GO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libtui)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

include_directories(${CMAKE_SOURCE_DIR}/VSinclude)
include_directories(${CMAKE_SOURCE_DIR}/sqlite_modern_cpp/hdr)

file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)

add_executable(VirtualShelf main.cpp ${SRC_FILES})

if (NOT DEFINED PLATFORM)
    message(FATAL_ERROR "You must specify -DPLATFORM=windows or -DPLATFORM=linux")
endif()

if (PLATFORM STREQUAL "windows")
    message(STATUS "Building for Windows")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    target_link_libraries(VirtualShelf msvcrt.lib legacy_stdio_definitions.lib)

    if (NOT DEFINED LIBTUI_PATH)
        message(FATAL_ERROR "LIBTUI_PATH must be specified for Windows build")
    endif()
    set(LIBTUI_OUTPUT ${LIBTUI_PATH})
    
elseif (PLATFORM STREQUAL "linux")
    message(STATUS "Building for Linux")
    set(LIBTUI_OUTPUT ${CMAKE_BINARY_DIR}/libtui.a)

    add_custom_command(
        OUTPUT ${LIBTUI_OUTPUT}
        COMMAND env GOOS=linux go build -buildmode=c-archive -o ${LIBTUI_OUTPUT} .
        WORKING_DIRECTORY ${GO_SOURCE_DIR}
        COMMENT "Building Go project as a static library for Linux"
    )
    
    add_custom_target(BuildLibtui ALL DEPENDS ${LIBTUI_OUTPUT})
    add_dependencies(VirtualShelf BuildLibtui)

else()
    message(FATAL_ERROR "Unknown PLATFORM: ${PLATFORM}")
endif()

add_library(libtui STATIC IMPORTED)
set_target_properties(libtui PROPERTIES IMPORTED_LOCATION ${LIBTUI_OUTPUT})

find_package(SQLite3 REQUIRED)
target_link_libraries(VirtualShelf libtui SQLite::SQLite3)

target_link_directories(VirtualShelf PRIVATE ${CMAKE_BINARY_DIR})

# GTest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/VSinclude)

add_executable(VirtualShelfTests ${TEST_FILES} ${SRC_FILES})
target_link_libraries(VirtualShelfTests GTest::GTest GTest::Main libtui SQLite::SQLite3)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS VirtualShelfTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all tests"
)

add_test(NAME VirtualShelfTests COMMAND VirtualShelfTests)
