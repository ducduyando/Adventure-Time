//========================Finn.h========================


#ifndef FINN_H
#define FINN_H

#include "Character.h"

class Finn : public Character
{
    public:
    void useSkill1();
    void useSkill2();
    void useSkill3();
    void shieldCancel();

    void initialize();
    void render(SDL_Renderer* renderer, Texture tex);
    void renderLogic(SDL_Renderer* renderer);
};


#endif //FINN_H
