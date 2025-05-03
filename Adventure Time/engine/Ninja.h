//========================Ninja.h========================


#ifndef NINJA_H
#define NINJA_H

#include "Character.h"


class Ninja : public Character
{
public:

    void useSkill1();
    void useSkill2();
    void useSkill3();
    void cloneCancel();
    void usingClone();

    void initialize();
    void render(SDL_Renderer* renderer, Texture tex);
    void renderLogic(SDL_Renderer* renderer);

    int ninjaShurikens;
    bool isCloning;
};

#endif //NINJA_H
