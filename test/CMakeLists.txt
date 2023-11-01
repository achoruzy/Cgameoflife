cmake_minimum_required(VERSION 3.26.0)

project(Cbuoy_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# raylib
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()

add_executable(${PROJECT_NAME} test_main.c)

# file(GLOB_RECURSE SOURCE_FILES "../src/*.c")
# file(GLOB_RECURSE HEADER_FILES "../src/*.h")

set(HEADER_FILES
    ../src/logic/convay_rules.h
    ../src/logic/cell.h
    ../src/logic/cell_utils.h
)

set(SOURCE_FILES
    ../src/logic/convay_rules.c
    ../src/logic/cell_utils.c
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} raylib)
