//========================Level.cpp========================

#include <iostream>
using namespace std;

#include "Character.h"
#include "Level.h"

void Level::initialize()
{
    idle.frame.limit = idle.texture->w/LEVEL_WIDTH;
}


void Level::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Level::renderLogic(SDL_Renderer* renderer)
{
    render(renderer,idle);
}

void Level::levelReset()
{
    idle.frame.currentFrame = 0;
    idle.clip.x = idle.frame.currentFrame * LEVEL_WIDTH;
}
