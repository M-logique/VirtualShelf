cmake_minimum_required(VERSION 3.10)
project(VirtualShelf)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_TESTS "Enable building tests" OFF)
set(AR "ar" CACHE STRING "Path of ar") 
set(GOOS "linux" CACHE STRING "GOOS environment variable")
set(GOARCH "amd64" CACHE STRING "GOARCH environment variable")

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(GO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libtui)
set(LIBTUI_PATH ${CMAKE_BINARY_DIR}/libtui.a)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/sqlite_modern_cpp/hdr)

file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)
file(GLOB GO_FILES ${GO_SOURCE_DIR}/*.go)

add_executable(VirtualShelf main.cpp ${SRC_FILES})

set(LIBSQLITE3_PATH ${CMAKE_BINARY_DIR}/libsqlite3.a)
set(SQLITE3_INCLUDE_DIR ${CMAKE_BINARY_DIR}/)  # Define a variable for the include directory

add_custom_target(BuildSQlite3 ALL DEPENDS ${LIBSQLITE3_PATH})


add_custom_command(
    OUTPUT ${LIBSQLITE3_PATH}
    COMMAND ${CMAKE_COMMAND} -E env
        AR=${AR}
        GCC=${CMAKE_C_COMPILER}
        python3 build_sqlite3.py -o ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/.github
    COMMENT "Building SQLite3 library"
)

# After SQLite3 build, add the include directory dynamically
add_custom_command(
    TARGET BuildSQlite3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SQLITE3_INCLUDE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/.github/sqlite3.h
        ${SQLITE3_INCLUDE_DIR}/sqlite3.h
    COMMENT "Copying sqlite3.h to include directory"
)

# Build Go project as a static library
add_custom_command(
    OUTPUT ${LIBTUI_PATH}
    COMMAND ${CMAKE_COMMAND} -E env
        GOOS=${GOOS}
        GOARCH=${GOARCH}
        CGO_ENABLED=1 
        CC=${CMAKE_C_COMPILER}
        CXX=${CMAKE_CXX_CIMPILER}
        go build -buildmode=c-archive -o ${LIBTUI_PATH} ${GO_FILES}
    WORKING_DIRECTORY ${GO_SOURCE_DIR}
    COMMENT "Building Go project as a static library"
)

# Define custom targets to ensure the required libraries are built
add_custom_target(BuildGolang ALL DEPENDS ${LIBTUI_PATH})

# Link necessary libraries to the VirtualShelf executable
target_link_libraries(VirtualShelf PRIVATE ${LIBTUI_PATH} ${LIBSQLITE3_PATH})
add_dependencies(VirtualShelf BuildGolang BuildSQlite3)

# Dynamically add SQLite3 include directory to the project after it's built
target_include_directories(VirtualShelf PRIVATE ${SQLITE3_INCLUDE_DIR})

# Enable tests if specified
if(DEFINED BUILD_TESTS AND BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    include_directories(${CMAKE_SOURCE_DIR}/include)

    add_executable(VirtualShelfTests ${TEST_FILES} ${SRC_FILES})

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
