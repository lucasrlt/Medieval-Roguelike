CORE =  core/Entity.cpp core/Game.cpp core/Projectile.cpp core/Weapon.cpp core/Player.cpp core/Room.cpp core/Vector2D.cpp core/DungeonGenerator.cpp core/TileMap.cpp core/Ghost.cpp core/Savage.cpp

SRCS_TXT = $(CORE) txt/TXTGame.cpp txt/WinTXT.cpp txt/main_txt.cpp
FINAL_TARGET_TXT = medieval_roguelike_txt
#DEFINE_TXT = -DJEU_TXT

SRCS_SDL = $(CORE) sdl2/SDLGame.cpp sdl2/main_sdl.cpp
FINAL_TARGET_SDL = medieval_roguelike_sdl
#DEFINE_SDL = -DJEU_SDL

SRCS_TEST = $(CORE) core/main_test.cpp 
FINAL_TARGET_TEST = medieval_roguelike_test
#DEFINE_REG = -DJEU_REG

ifeq ($(OS),Windows_NT)
	INCLUDE_DIR_SDL = 	-Iextern/SDL2_mingw/SDL2-2.0.3/include \
						-Iextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2 \
						-Iextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/include/SDL2

	LIBS_SDL = -Lextern \
			-Lextern/SDL2_mingw/SDL2-2.0.3/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_ttf-2.0.12/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_image-2.0.0/i686-w64-mingw32/lib \
			-Lextern/SDL2_mingw/SDL2_mixer-2.0.1/i686-w64-mingw32/lib \
			-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_ttf.dll -lSDL2_image.dll -lSDL2_mixer.dll

else
	INCLUDE_DIR_SDL = -I/usr/include/SDL2 -I/usr/local/include/SDL2
	LIBS_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image
endif

CC					= g++
LD 					= g++
LDFLAGS  			=
CPPFLAGS 			= -Wall -ggdb  -std=c++11 #-O2   # pour optimiser
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -Isrc/core -Isrc/sdl2 -Itxt

default: make_dir $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL) $(BIN_DIR)/$(FINAL_TARGET_TEST)

make_dir:
ifeq ($(OS),Windows_NT)
	if not exist $(OBJ_DIR) mkdir $(OBJ_DIR) $(OBJ_DIR)\txt $(OBJ_DIR)\sdl2 $(OBJ_DIR)\core $(OBJ_DIR)\qt
else
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) $(OBJ_DIR)/txt $(OBJ_DIR)/sdl2 $(OBJ_DIR)/core
endif

$(BIN_DIR)/$(FINAL_TARGET_TXT): $(SRCS_TXT:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(BIN_DIR)/$(FINAL_TARGET_SDL): $(SRCS_SDL:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIBS_SDL)

$(BIN_DIR)/$(FINAL_TARGET_TEST): $(SRCS_TEST:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR_SDL) $(INCLUDE_DIR) $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\txt\*.o $(OBJ_DIR)\sdl2\*.o $(OBJ_DIR)\core\*.o $(BIN_DIR)\$(FINAL_TARGET_TXT).exe $(BIN_DIR)\$(FINAL_TARGET_SDL).exe $(BIN_DIR)\$(FINAL_TARGET_TEST).exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(FINAL_TARGET_TXT) $(BIN_DIR)/$(FINAL_TARGET_SDL)
endif

grind:
	valgrind --tool=memcheck --leak-check=full --undef-value-errors=no bin/medieval_roguelike_sdl