cmake_minimum_required(VERSION 3.26.0)

project(Cbuoy)
set(CMAKE_C_STANDARD 99)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../include)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
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

set(SOURCES
    ./main.c
)
set(HEADERS
    src/logic/logic.h
    src/draw/draw_cell.h
    src/draw/draw_grid.h
    src/input/cells.h
)
set(CFILES
    src/logic/logic.c
    src/draw/draw_cell.c
    src/draw/draw_grid.c
    src/input/cells.c
)

# file(GLOB_RECURSE sources src/*.c src/*.h main.c)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME} ${CFILES} ${SOURCES} ${HEADERS})
# add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} raylib)