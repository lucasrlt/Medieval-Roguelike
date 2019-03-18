cmake_minimum_required(VERSION 3.13)
project(medieval_roguelike)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(medieval_roguelike src/core/main.cpp src/core/Game.h src/core/Game.cpp src/core/Player.h src/core/Player.cpp src/core/Weapon.h src/core/Weapon.cpp src/core/DungeonGenerator.cpp src/core/DungeonGenerator.h src/core/Room.cpp src/core/Room.h src/core/Vector2D.cpp src/core/Vector2D.h src/core/Entity.cpp src/core/Entity.h src/core/TileMap.cpp src/core/TileMap.h src/txt/TXTGame.cpp src/txt/TXTGame.h src/txt/WinTXT.cpp src/txt/WinTXT.h src/sdl2/SDLGame.cpp)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

target_link_libraries(medieval_roguelike ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES})

