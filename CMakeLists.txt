cmake_minimum_required(VERSION 3.10)
project(VirtualShelf)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Enable building tests" OFF)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(GO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libtui)
set(LIBTUI_PATH ${CMAKE_BINARY_DIR}/libtui.a)

include_directories(${CMAKE_SOURCE_DIR}/VSinclude)
include_directories(${CMAKE_SOURCE_DIR}/sqlite_modern_cpp/hdr)

file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
file(GLOB GO_FILES ${GO_SOURCE_DIR}/*.go)

add_executable(VirtualShelf main.cpp ${SRC_FILES})

if (MSVC)
    # Define compiler flag to avoid security warnings
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    target_link_libraries(VirtualShelf PRIVATE msvcrt.lib legacy_stdio_definitions.lib)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

    # Link against SQLite3 for MSVC
    set(LIBSQLITE3_PATH ${CMAKE_BINARY_DIR}/sqlite3.lib)
    add_custom_command(
        OUTPUT ${LIBSQLITE3_PATH}
        COMMAND python3 build_sqlite3.py -o ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/.github
        COMMENT "Building SQLite3 library (for Windows)"
    )
else()
    # For Unix-like systems (Linux, macOS)
    set(LIBSQLITE3_PATH ${CMAKE_BINARY_DIR}/libsqlite3.a)
    add_custom_command(
        OUTPUT ${LIBSQLITE3_PATH}
        COMMAND python3 build_sqlite3.py -o ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/.github
        COMMENT "Building SQLite3 library (for Unix)"
    )
endif()

# Build Go project as a static library
add_custom_command(
    OUTPUT ${LIBTUI_PATH}
    COMMAND go build -buildmode=c-archive -o ${LIBTUI_PATH} ${GO_FILES}
    WORKING_DIRECTORY ${GO_SOURCE_DIR}
    COMMENT "Building Go project as a static library"
)

# Define custom targets to ensure the required libraries are built
add_custom_target(BuildGolang ALL DEPENDS ${LIBTUI_PATH})
add_custom_target(BuildSQlite3 ALL DEPENDS ${LIBSQLITE3_PATH})

# Link necessary libraries to the VirtualShelf executable
target_link_libraries(VirtualShelf PRIVATE ${LIBTUI_PATH} ${LIBSQLITE3_PATH})
add_dependencies(VirtualShelf BuildGolang BuildSQlite3)

# Enable tests if specified
if(DEFINED BUILD_TESTS AND BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    include_directories(${CMAKE_SOURCE_DIR}/VSinclude)

    add_executable(VirtualShelfTests ${TEST_FILES} ${SRC_FILES})

    if(MSVC)
        # Use MSVC runtime flags for the tests
        target_link_libraries(VirtualShelfTests PRIVATE msvcrt.lib legacy_stdio_definitions.lib)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    endif()

    # Link GTest and other libraries for testing
    target_link_libraries(
        VirtualShelfTests 
        PRIVATE 
        GTest::GTest 
        GTest::Main 
        ${LIBSQLITE3_PATH} 
        ${LIBTUI_PATH}
    )

    add_custom_target(run_tests
        COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS VirtualShelfTests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Running all tests"
    )

    add_test(NAME VirtualShelfTests COMMAND VirtualShelfTests)
endif()