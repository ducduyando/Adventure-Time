//========================Texture.h========================

#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL3/SDL.h>

struct FrameData
{
    float currentFrame = 0;
    Uint32 lastFrameTime = 0;
    int delay;
    int limit;
};

struct Texture
{
    public:
    SDL_FRect rect;
    SDL_Texture* texture;
    FrameData frame;
    SDL_FRect clip;
};

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path);
void updateFrame(Texture& texture, int maxFrames, int width);
void updateLayer(Texture& layer, float distance);
void move(Texture& texture, float coordinate, int maxFrames, int width);
void moveArrow(Texture& texture);

#endif
