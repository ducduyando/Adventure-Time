//========================Main.cpp========================
#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;
    if (!game.defaultInit() || !game.musicInit() || !game.menuInit() || !game.gameInit() || !game.levelInit()) {return 1;}
    game.run();
    game.cleanup();
    return 0;
}