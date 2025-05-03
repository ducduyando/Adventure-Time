//========================Texture.cpp========================

#include "Texture.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

#include "Constants.h"

using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path)
{
    SDL_Texture* tex = IMG_LoadTexture(renderer, path);
    if (!tex) {
        cout << "Unable to load texture: " << path << endl;
    }
    return tex;
}

void updateFrame(Texture& texture, int maxFrames, int width) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - texture.frame.lastFrameTime >= texture.frame.delay)
    {
        texture.frame.currentFrame = (int)(texture.frame.currentFrame + 1) % maxFrames;
        texture.frame.lastFrameTime = currentTime;
    }
    texture.clip.x = texture.frame.currentFrame * width;
}

void updateLayer(Texture& layer ,float distance)
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - layer.frame.lastFrameTime >= 15)
    {
        if (layer.rect.x - distance <= -SCREEN_WIDTH){layer.rect.x = SCREEN_WIDTH;}
        else{layer.rect.x -= distance;}
        layer.frame.lastFrameTime = currentTime;
    }
}

void move(Texture& texture, float coordinate, int maxFrames, int width)
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - texture.frame.lastFrameTime >= texture.frame.delay)
    {
        if (texture.rect.x - 10 <= coordinate){texture.rect.x = coordinate;}
        else{texture.rect.x -= 10;}
        texture.frame.currentFrame = (int)(texture.frame.currentFrame + 1) % maxFrames;
        texture.frame.lastFrameTime = currentTime;
    }

    texture.clip.x = texture.frame.currentFrame * width;
}

void moveArrow(Texture& texture)
{
    if (texture.clip.y == 0){texture.clip.y = SCREEN_HEIGHT;}
    else {texture.clip.y = 0;}
}
