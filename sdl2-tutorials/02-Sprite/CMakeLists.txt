find_package(SDL2 REQUIRED)

add_executable (sdl2-sprite sdl2-sprite.cpp)
target_link_libraries(sdl2-sprite PRIVATE SDL2::SDL2 SDL2::SDL2main)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sdl2-sprite PROPERTY CXX_STANDARD 20)
endif()
