cmake_minimum_required(VERSION 3.10)
project(VirtualShelf)

set(CMAKE_CXX_STANDARD 14)

set(GO_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libtui)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

include_directories(${CMAKE_SOURCE_DIR}/VSinclude)
include_directories(${CMAKE_SOURCE_DIR}/sqlite_modern_cpp/hdr)

file(GLOB SRC_FILES ${SRC_DIR}/*.cpp)
file(GLOB GO_FILES ${GO_SOURCE_DIR}/*.go)
file(GLOB TEST_FILES ${TEST_DIR}/*.cpp)

add_executable(VirtualShelf main.cpp ${SRC_FILES})

if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(LIBTUI_OUTPUT ${CMAKE_BINARY_DIR}/libtui.lib)
    target_link_libraries(VirtualShelf msvcrt.lib legacy_stdio_definitions.lib)
else()
    set(LIBTUI_OUTPUT ${CMAKE_BINARY_DIR}/libtui.a)
endif()

add_custom_command(
    OUTPUT ${LIBTUI_OUTPUT}
    COMMAND go build -buildmode=c-archive -o ${LIBTUI_OUTPUT} ${GO_FILES}
    WORKING_DIRECTORY ${GO_SOURCE_DIR}
    COMMENT "Building Go project as a static library"
)

add_library(libtui STATIC IMPORTED)
set_target_properties(libtui PROPERTIES IMPORTED_LOCATION ${LIBTUI_OUTPUT})

add_custom_target(BuildLibtui ALL DEPENDS ${LIBTUI_OUTPUT})
add_dependencies(VirtualShelf BuildLibtui)

set(CMAKE_TOOLCHAIN_FILE "$ENV{CMAKE_TOOLCHAIN_FILE}" CACHE STRING "")

find_package(SQLite3 REQUIRED)
target_include_directories(VirtualShelf PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(VirtualShelf PRIVATE ${SQLite3_LIBRARIES})

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(VirtualShelfTests ${TEST_FILES} ${SRC_FILES})
target_link_libraries(VirtualShelfTests GTest::GTest GTest::Main libtui SQLite::SQLite3)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS VirtualShelfTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all tests"
)

add_test(NAME VirtualShelfTests COMMAND VirtualShelfTests)


# if(WIN32)
#     # Windows-specific options
#     add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

#     add_custom_command(
#         OUTPUT ${CMAKE_BINARY_DIR}/libtui.a
#         COMMAND go build -buildmode=c-archive -o ${CMAKE_BINARY_DIR}/libtui.a ${GO_FILES}
#         WORKING_DIRECTORY ${GO_SOURCE_DIR}
#         COMMENT "Building Go project as a static library (Windows)"
#     )

#     target_link_libraries(VirtualShelf msvcrt.lib legacy_stdio_definitions.lib)

# elseif(UNIX)
#     # Linux-specific options
#     add_custom_command(
#         OUTPUT ${CMAKE_BINARY_DIR}/libtui.a
#         COMMAND go build -buildmode=c-archive -o ${CMAKE_BINARY_DIR}/libtui.a ${GO_FILES}
#         WORKING_DIRECTORY ${GO_SOURCE_DIR}
#         COMMENT "Building Go project as a static library (Linux)"
#     )
# endif()

# find_package(SQLite3 REQUIRED)
# add_custom_target(BuildLibtui ALL DEPENDS ${CMAKE_BINARY_DIR}/libtui.a)
# target_link_libraries(VirtualShelf ${CMAKE_BINARY_DIR}/libtui.a PRIVATE SQLite::SQLite3)



# add_dependencies(VirtualShelf BuildLibtui)