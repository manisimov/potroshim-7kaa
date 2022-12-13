cmake_minimum_required (VERSION 3.18)
project (7kaa)

set (CMAKE_BUILD_TYPE Debug)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
find_package (SDL2)
find_package (SDL2_image)

add_subdirectory (01_SDL_hello)
add_subdirectory (02_Main_cursor)
add_subdirectory (03_Map_terrain)
add_subdirectory (04_Map_generate)
