cmake_minimum_required(VERSION 3.13)
project(medieval_roguelike)

set(CMAKE_CXX_STANDARD 14)

add_executable(medieval_roguelike
        "data/tilemaps/Capture d’écran 2019-03-05 à 09.06.46.png"
        doc/doxyfile
        src/main.cpp
        CMakeLists.txt
        README src/Vector2D.cpp src/Vector2D.h src/Entity.cpp src/Entity.h src/Player.cpp src/Player.h src/Weapon.cpp src/Weapon.h)
