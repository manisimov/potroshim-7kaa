add_executable (sdl_hello main.c)
target_include_directories (sdl_hello PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries (sdl_hello PRIVATE SDL2::Main SDL2::Image)
