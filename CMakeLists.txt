cmake_minimum_required(VERSION 3.13)
project(medieval_roguelike)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_executable(medieval_roguelike src/main.cpp  src/Room.cpp src/Room.h src/Vector2D.cpp src/Vector2D.h src/Agent.cpp src/Agent.h src/TileMap.cpp src/TileMap.h)
