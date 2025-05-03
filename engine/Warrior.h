//========================Warrior.h========================


#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"


class Warrior : public Character
{
public:

    void useSkill1();
    void useSkill2();
    void useSkill3();
    void shieldCancel();

    void initialize();
    void render(SDL_Renderer* renderer, Texture tex);
    void renderLogic(SDL_Renderer* renderer);

    bool checkHp;
    bool checkHit;
};

#endif //WARRIOR_H
