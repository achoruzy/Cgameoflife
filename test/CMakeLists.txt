cmake_minimum_required(VERSION 3.26.0)

project(Cbuoy_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(${PROJECT_NAME} test_main.c)

# file(GLOB_RECURSE SOURCE_FILES "../src/*.c")
# file(GLOB_RECURSE HEADER_FILES "../src/*.h")

set(HEADER_FILES
    ../src/logic/convay_rules.h
    ../src/logic/cell.h
)

set(SOURCE_FILES
    ../src/logic/convay_rules.c
    ../src/logic/cell.c
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
