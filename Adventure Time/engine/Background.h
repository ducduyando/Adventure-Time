//========================Background.h========================


#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Texture.h"
#include "Constants.h"

class Background
{
    public:

    Texture Layer1A;
    Texture Layer1B;
    Texture Layer2A;
    Texture Layer2B;
    Texture Layer3A;
    Texture Layer3B;
    Texture Layer4A;
    Texture Layer4B;
    Texture Layer5A;
    Texture Layer5B;

    void loadBackground(SDL_Renderer* renderer, float x, float y);
    void render(SDL_Renderer* renderer, Texture tex);
    void updateBackground();
    void renderLogic(SDL_Renderer* renderer);
};


#endif //BACKGROUND_H
