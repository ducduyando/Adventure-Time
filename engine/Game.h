//========================Game.h========================

#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include "Texture.h"
#include "Music.h"
#include "Finn.h"
#include "Skeleton.h"
#include "Warrior.h"
#include "Ninja.h"
#include "Background.h"
#include "Menu.h"
#include "Level.h"
#include <map>

class Game
{
    public:
    Game();
    void run();
    void cleanup();
    bool defaultInit();
    bool musicInit();
    bool menuInit();
    bool gameInit();
    bool levelInit();
    void playMusic(Mix_Music* musicToPlay);
    void defaultRender();

    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Mix_Music* currentMusic;
    Music MUSIC;
    Finn FINN;
    Skeleton SKELETON;
    Warrior WARRIOR;
    Ninja NINJA;
    Background BACKGROUND;
    Level LEVEL;
    Menu MENU;
    Menu DIFFICULTYMODE;
    Menu LOADING;
    Menu WIN;
    Menu LOSE;
    bool running;
    bool menu;
    bool chooseGameMode;
    bool loading;
    bool playAgain;
    double level;
    string gameMode;

    void reset();
    void menuLogic();
    void levelLogic();
    void gameLogic();
    void randomSkillEasy(int delay);
    void randomSkillHard(int delay);
    void gameHandle(SDL_Event& e);
};

#endif //GAME_H
