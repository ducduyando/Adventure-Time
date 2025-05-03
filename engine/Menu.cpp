//========================Menu.cpp========================
#include <iostream>
using namespace std;

#include "Character.h"
#include "Menu.h"

void Menu::initialize()
{
    idle.frame.limit = idle.texture->w/SCREEN_WIDTH;
}


void Menu::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Menu::renderLogic(SDL_Renderer* renderer)
{
    render(renderer,idle);
}

bool Menu::gameStart()
{
    if (idle.clip.y == 0){return true;}
    else {return false;}
}

void Menu::menuReset()
{
    idle.frame.currentFrame = 0;
    idle.clip.x = idle.frame.currentFrame * SCREEN_WIDTH;
}