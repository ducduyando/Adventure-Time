//========================Skeleton.h========================


#ifndef SKELETON_H
#define SKELETON_H

#include "Character.h"


class Skeleton : public Character
{
    public:

    void useSkill1();
    void useSkill2();
    void useSkill3();
    void shieldCancel();

    void initialize();
    void render(SDL_Renderer* renderer, Texture tex);
    void renderLogic(SDL_Renderer* renderer);

    int skeletonArrows;
};


#endif //SKELETON_H
