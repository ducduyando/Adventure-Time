//========================Warrior.cpp========================


#include <iostream>
using namespace std;

#include "Character.h"
#include "Warrior.h"

void Warrior::initialize()
{
    channel["Get hit"] = 20;
    channel["Run"] = 21;
    music.loadSFX("Dead");channel["Dead"] = 22;
    music.loadSFX("Sword");channel["Sword"] = 23;
    music.loadSFX("Hp up");channel["Hp up"] = 24;
    music.loadSFX("Shield up");channel["Shield up"] = 25;
    isUsingSkill1 = false;
    isUsingSkill2 = false;
    isUsingSkill3 = false;
    isGettingDamaged = false;
    isGettingKilled = false;
    isRunning = false;
    isDead = false;
    idle.frame.limit = idle.texture->w/SPRITE_WIDTH;
    healthBar.frame.limit = healthBar.texture->w/BAR_WIDTH;
    energyBar.frame.limit = energyBar.texture->w/BAR_WIDTH;
    skill1.frame.limit = skill1.texture->w/SPRITE_WIDTH;
    skill2.frame.limit = skill2.texture->w/SPRITE_WIDTH;
    skill3.frame.limit = skill3.texture->w/SPRITE_WIDTH;
    getDamaged.frame.limit = getDamaged.texture->w/SPRITE_WIDTH;
    getKilled.frame.limit = getKilled.texture->w/SPRITE_WIDTH;
    run.frame.limit = run.texture->w/SPRITE_WIDTH;
    checkHp = true;
    checkHit = true;
}

void Warrior::useSkill1()
{
    if (!isUsingSkill1 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Sword", channel["Sword"]);
        isUsingSkill1 = true;
        skill1.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Warrior::useSkill2()
{
    if (!isUsingSkill2 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Hp up", channel["Hp up"]);
        isUsingSkill2 = true;
        skill2.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Warrior::useSkill3()
{
    if (!isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 3)
    {
        music.playSFX("Sword", channel["Sword"]);
        music.playSFX("Shield up", channel["Shield up"]);
        isUsingSkill3 = true;
        skill3.frame.currentFrame = 0;
        loseMana(3);
    }
}

void Warrior::shieldCancel()
{
    isUsingSkill3 = false;
}

void Warrior::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Warrior::renderLogic(SDL_Renderer* renderer)
{
    render(renderer, healthBar);
    render(renderer, energyBar);

    if (!isDead)
    {
        if (isUsingSkill1){render(renderer, skill1);}
        else if (isUsingSkill3){render(renderer, skill3);}
        else if (isGettingDamaged){render(renderer, getDamaged);}
        else if (isGettingKilled){render(renderer, getKilled);}
        else if (isRunning){render(renderer, run);}
        else{render(renderer, idle);}
        if (isUsingSkill2){render(renderer, skill2);}
    }
}
