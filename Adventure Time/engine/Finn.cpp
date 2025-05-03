//========================Finn.cpp========================


#include <iostream>
using namespace std;

#include "Character.h"
#include "Finn.h"

void Finn::initialize()
{
    channel["Get hit"] = 0;
    channel["Run"] = 1;
    music.loadSFX("Stage win");channel["Stage win"] = 2;
    music.loadSFX("Shield block");channel["Shield block"] = 3;
    music.loadSFX("Dead");channel["Dead"] = 4;
    music.loadSFX("Sword");channel["Sword"] = 5;
    music.loadSFX("Power up");channel["Power up"] = 6;
    music.loadSFX("Charge up");channel["Charge up"] = 7;
    isUsingSkill1 = false;
    isUsingSkill2 = false;
    isUsingSkill3 = false;
    isGettingDamaged = false;
    isGettingKilled = false;
    isDead = false;
    isRunning = true;
    idle.frame.limit = idle.texture->w/SPRITE_WIDTH;
    healthBar.frame.limit = healthBar.texture->w/BAR_WIDTH;
    energyBar.frame.limit = energyBar.texture->w/BAR_WIDTH;
    skill1.frame.limit = skill1.texture->w/SPRITE_WIDTH;
    skill2.frame.limit = skill2.texture->w/SPRITE_WIDTH;
    skill3.frame.limit = skill3.texture->w/SPRITE_WIDTH;
    getDamaged.frame.limit = getDamaged.texture->w/SPRITE_WIDTH;
    getKilled.frame.limit = getKilled.texture->w/SPRITE_WIDTH;
    run.frame.limit = run.texture->w/SPRITE_WIDTH;
}

void Finn::useSkill1()
{
    if (!isUsingSkill1 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Sword", channel["Sword"]);
        isUsingSkill1 = true;
        skill1.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Finn::useSkill2()
{
    if (!isUsingSkill2 && !isGettingDamaged && energyBar.frame.currentFrame >= 1)
    {
        music.playSFX("Power up", channel["Power up"]);
        isUsingSkill2 = true;
        skill2.frame.currentFrame = 0;
        loseMana(1);
    }
}

void Finn::useSkill3()
{
    if (!isUsingSkill1 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Charge up", channel["Charge up"]);
        isUsingSkill3 = true;
        skill3.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Finn::shieldCancel()
{
    isUsingSkill2 = false;
}

void Finn::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Finn::renderLogic(SDL_Renderer* renderer)
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