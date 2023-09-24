find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(sdl2-gameloop
	sdl2-main.cpp
	application.h
	application.cpp
	sprite.h)

target_link_libraries(sdl2-gameloop PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET sdl2-gameloop PROPERTY CXX_STANDARD 20)
endif()
