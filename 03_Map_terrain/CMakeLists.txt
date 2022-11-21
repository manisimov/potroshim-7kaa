add_executable (03_Map_terrain main.cpp
  screen.cpp
  world.cpp
  )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
target_include_directories (03_Map_terrain PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries (03_Map_terrain PRIVATE SDL2::Main SDL2::Image)
