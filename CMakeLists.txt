cmake_minimum_required(VERSION 3.13)
project(medieval_roguelike)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(medieval_roguelike src/main.cpp src/Game.h src/Game.cpp src/Player.h src/Player.cpp src/Weapon.h src/Weapon.cpp src/DungeonGenerator.cpp src/DungeonGenerator.h src/Room.cpp src/Room.h src/Vector2D.cpp src/Vector2D.h src/Entity.cpp src/Entity.h src/TileMap.cpp src/TileMap.h src/txt/TextMode.cpp src/txt/TextMode.h src/txt/WinTXT.cpp src/txt/WinTXT.h src/SDLGame.cpp src/SDLGame.h)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(medieval_roguelike ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

