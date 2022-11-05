add_executable (02_Main_cursor AM.cpp
  OSYS.cpp
  OVGA.cpp
  OVGABUF.cpp
  OVGABUF2.cpp
  OMOUSECR.cpp
  OMOUSE.cpp
  OGAMMAIN.cpp)
target_include_directories (02_Main_cursor PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries (02_Main_cursor PRIVATE SDL2::Main SDL2::Image)
