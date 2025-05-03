//========================Menu.h========================


#ifndef MENU_H
#define MENU_H

#include "Character.h"

class Menu : public Character
{
    public:

    void initialize();
    void render(SDL_Renderer* renderer, Texture tex);
    void renderLogic(SDL_Renderer* renderer);
    void menuReset();

    bool gameStart();
};

#endif //MENU_H
