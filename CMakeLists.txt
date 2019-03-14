cmake_minimum_required(VERSION 3.13)
project(medieval_roguelike)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_executable(medieval_roguelike src/main.cpp src/Player.h src/Player.cpp src/Weapon.h src/Weapon.cpp src/DungeonGenerator.cpp src/DungeonGenerator.h src/Room.cpp src/Room.h src/Vector2D.cpp src/Vector2D.h src/Entity.cpp src/Entity.h src/TileMap.cpp src/TileMap.h src/SDLGame.h)
