add_executable (04_Map_generate main.cpp
  screen.cpp
  world.cpp
  height_map.cpp
  rand.cpp
  )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
target_include_directories (04_Map_generate PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries (04_Map_generate PRIVATE SDL2::Main SDL2::Image)
