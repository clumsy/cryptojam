cmake_minimum_required(VERSION 3.6)
project(cryptojam)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

include_directories(${PROJECT_SOURCE_DIR}/src/main/c)
include_directories(${PROJECT_SOURCE_DIR}/src/test/c)
include_directories(${PROJECT_BINARY_DIR})

set(SOURCE_FILES
    src/main/c/base58.c src/main/c/base58.h
    src/main/c/sha1.c src/main/c/sha1.h
    src/main/c/sha2.c src/main/c/sha2.h
    src/main/c/utils.c src/main/c/utils.h
    src/main/c/base58check.c src/main/c/base58check.h)
add_executable(cryptojam ${SOURCE_FILES} src/main/c/main.c)

set(TEST_FILES
    src/test/c/CuTest.h src/test/c/CuTest.c src/test/c/AllTests.c
    src/test/c/base58_test.c
    src/test/c/base58check_test.c
    src/test/c/sha1_test.c
    src/test/c/sha2_test.c
    src/test/c/utils_test.c)
add_executable(cryptojam-test ${TEST_FILES} ${SOURCE_FILES})
add_test(test ${PROJECT_BINARY_DIR}/cryptojam-test)
