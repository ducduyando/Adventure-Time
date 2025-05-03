//========================Character.cpp========================



#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "Texture.h"
#include "Constants.h"
#include "Music.h"

using namespace std;
class Character
{
    public:
    map<string, int> channel;
    Music music;
    Texture idle;
    Texture healthBar;
    Texture energyBar;
    Texture skill1;
    bool isUsingSkill1;
    Texture skill2;
    bool isUsingSkill2;
    Texture skill3;
    bool isUsingSkill3;
    Texture getDamaged;
    bool isGettingDamaged;
    Texture getKilled;
    bool isGettingKilled;
    bool isDead;
    Texture run;
    bool isRunning;

    void loadMedia(SDL_Renderer* renderer, string name, float x, float y);
    void defaultSFX();
    void systemPlay(string name);
    void takeDamage(float amount);
    void heal(float amount);
    void loseMana(float amount);
    void die();
    void reset();
    void npcRespawn();

};

#endif //CHARACTER_H
