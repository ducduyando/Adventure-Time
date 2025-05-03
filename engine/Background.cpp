//========================Background.cpp========================
#include <iostream>
using namespace std;

#include "Character.h"
#include "Background.h"



void Background::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Background::loadBackground(SDL_Renderer* renderer, float x, float y)
{
    Layer1A = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"1.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer1B = {{x + SCREEN_WIDTH, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"1.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer2A = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"2.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer2B = {{ x + SCREEN_WIDTH, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"2.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer3A = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"3.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer3B = {{x + SCREEN_WIDTH, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"3.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer4A = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"4.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer4B = {{x + SCREEN_WIDTH, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"4.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer5A = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"5.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
    Layer5B = {{x + SCREEN_WIDTH, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+"5.png").c_str()), {0, 0, SPRITE_DELAY}, {0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};
}


void Background::updateBackground()
{
    updateLayer(Layer1A, 1);
    updateLayer(Layer1B, 1);
    updateLayer(Layer2A, 2);
    updateLayer(Layer2B, 2);
    updateLayer(Layer3A, 3);
    updateLayer(Layer3B, 3);
    updateLayer(Layer4A, 4);
    updateLayer(Layer4B, 4);
    updateLayer(Layer5A, 5);
    updateLayer(Layer5B, 5);
}


void Background::renderLogic(SDL_Renderer* renderer)
{
    render(renderer,Layer1A);
    render(renderer,Layer1B);
    render(renderer,Layer2A);
    render(renderer,Layer2B);
    render(renderer,Layer3A);
    render(renderer,Layer3B);
    render(renderer,Layer4A);
    render(renderer,Layer4B);
    render(renderer,Layer5A);
    render(renderer,Layer5B);

}