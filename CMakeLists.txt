cmake_minimum_required(VERSION 3.10.2)
project(Ski_Safari C)

set(CMAKE_C_STANDARD 11)

link_libraries(winmm SDL2 SDL2_image)

add_executable(Ski_Safari game.c wave.c wave.h player.c player.h background.c background.h resource.c resource.h camera.c camera.h obstacle.c obstacle.h flowey.c flowey.h gui.c gui.h)
