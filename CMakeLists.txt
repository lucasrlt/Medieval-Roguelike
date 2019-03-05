cmake_minimum_required(VERSION 3.13)
project(MedievalRogueLike)

set(CMAKE_CXX_STANDARD 14)

add_executable(MedievalRogueLike src/main.cpp src/LevelGenerator.cpp src/LevelGenerator.h src/Room.cpp src/Room.h)