//========================Level.h========================


#ifndef LEVEL_H
#define LEVEL_H

#include "Character.h"

class Level : public Character
{
public:
    void initialize();
    void render(SDL_Renderer* renderer, Texture tex);
    void renderLogic(SDL_Renderer* renderer);
    void levelReset();
};


#endif //LEVEL_H
