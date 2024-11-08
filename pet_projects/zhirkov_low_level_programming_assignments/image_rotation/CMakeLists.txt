cmake_minimum_required(VERSION 3.12)

# Project name
project(assignment_image_rotation C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Wshadow ")
# -Werror
include_directories( GLOB_RECURSE ${PROJECT_SOURCE_DIR}/include)


set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")


#file()

file(GLOB_RECURSE SOURCES "src/*.c")

# Create a library from the source files
add_library(library_for_tests ${SOURCES})


message(STATUS "Source files: ${SOURCES}")

enable_testing()

# Tests
add_executable(test_1 "tester/test_image_1_rotation.c")
add_executable(test_2 "tester/test_image_2_rotation.c")
add_executable(test_3 "tester/test_image_3_rotation.c")
add_executable(test_4 "tester/test_image_4_rotation.c")
add_executable(test_5 "tester/test_image_5_rotation.c")
add_executable(test_6 "tester/test_image_6_rotation.c")

target_link_libraries(test_1 library_for_tests)
target_link_libraries(test_2 library_for_tests)
target_link_libraries(test_3 library_for_tests)
target_link_libraries(test_4 library_for_tests)
target_link_libraries(test_5 library_for_tests)
target_link_libraries(test_6 library_for_tests)

# Register tests with CTest
add_test(NAME TEST_1 COMMAND test_1)
add_test(NAME TEST_2 COMMAND test_2)
add_test(NAME TEST_3 COMMAND test_3)
add_test(NAME TEST_4 COMMAND test_4)
add_test(NAME TEST_5 COMMAND test_5)
add_test(NAME TEST_6 COMMAND test_6)

# Main program
add_executable(image-transformer ${SOURCES}
        include/image/bmp/bmp_header_constants.h
        include/constants.h
        include/image/bmp/bmp_utilities.h
        src/image/bmp/bmp_utilities.c)

# Configure sanitizers based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "ASan")
    message(STATUS "Using AddressSanitizer")
    set_target_properties(image-transformer PROPERTIES
        COMPILE_FLAGS "-fsanitize=address"
        LINK_FLAGS "-fsanitize=address")
elseif(CMAKE_BUILD_TYPE STREQUAL "LSan")
    message(STATUS "Using LeakSanitizer")
    set_target_properties(image-transformer PROPERTIES
        COMPILE_FLAGS "-fsanitize=leak"
        LINK_FLAGS "-fsanitize=leak")
elseif(CMAKE_BUILD_TYPE STREQUAL "MSan")
    message(STATUS "Using MemorySanitizer")
    set_target_properties(image-transformer PROPERTIES
        COMPILE_FLAGS "-fsanitize=memory"
        LINK_FLAGS "-fsanitize=memory")
elseif(CMAKE_BUILD_TYPE STREQUAL "UBSan")
    message(STATUS "Using UndefinedBehaviourSanitizer")
    set_target_properties(image-transformer PROPERTIES
        COMPILE_FLAGS "-fsanitize=undefined"
        LINK_FLAGS "-fsanitize=undefined")
endif()