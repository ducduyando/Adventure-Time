//========================Ninja.cpp========================


#include <iostream>
using namespace std;

#include "Character.h"
#include "Ninja.h"

void Ninja::initialize()
{
    channel["Get hit"] = 30;
    channel["Run"] = 31;
    music.loadSFX("Dead");channel["Dead"] = 32;
    music.loadSFX("Sword");channel["Sword"] = 33;
    music.loadSFX("Shuriken");channel["Shuriken"] = 34;
    music.loadSFX("Shadow clone");channel["Shadow clone"] = 35;
    isUsingSkill1 = false;
    isUsingSkill2 = false;
    isUsingSkill3 = false;
    isGettingDamaged = false;
    isGettingKilled = false;
    isDead = false;
    isRunning = false;
    idle.frame.limit = idle.texture->w/SPRITE_WIDTH;
    healthBar.frame.limit = healthBar.texture->w/BAR_WIDTH;
    energyBar.frame.limit = energyBar.texture->w/BAR_WIDTH;
    skill1.frame.limit = skill1.texture->w/SPRITE_WIDTH;
    skill2.frame.limit = skill2.texture->w/SPRITE_WIDTH;
    skill3.frame.limit = skill3.texture->w/SPRITE_WIDTH;
    getDamaged.frame.limit = getDamaged.texture->w/SPRITE_WIDTH;
    getKilled.frame.limit = getKilled.texture->w/SPRITE_WIDTH;
    run.frame.limit = run.texture->w/SPRITE_WIDTH;
    ninjaShurikens = 2;
}

void Ninja::useSkill1()
{
    if (!isUsingSkill1 && !isUsingSkill2 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 3)
    {
        music.playSFX("Sword", channel["Sword"]);
        isUsingSkill1 = true;
        skill1.frame.currentFrame = 0;
        loseMana(3);
    }
}

void Ninja::useSkill2()
{
    if (!isUsingSkill1 && !isUsingSkill2 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 3)
    {
        music.playSFX("Shuriken", channel["Shuriken"]);
        ninjaShurikens = 2;
        isUsingSkill2 = true;
        skill2.frame.currentFrame = 0;
        loseMana(3);
    }
}

void Ninja::useSkill3()
{
    if (!isUsingSkill1 && !isUsingSkill2 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Shadow clone", channel["Shadow clone"]);
        isUsingSkill3 = true;
        skill3.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Ninja::cloneCancel()
{
    isCloning = false;
    isUsingSkill3 = false;
}

void Ninja::usingClone()
{
    if (isCloning)
    {
        idle.clip.y = SPRITE_HEIGHT;
        skill1.clip.y = SPRITE_HEIGHT;
        skill2.clip.y = SPRITE_HEIGHT;
    }
    else
    {
        idle.clip.y = 0;
        skill1.clip.y = 0;
        skill2.clip.y = 0;
    }
}

void Ninja::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Ninja::renderLogic(SDL_Renderer* renderer)
{
    render(renderer, healthBar);
    render(renderer, energyBar);

    if (!isDead)
    {
        if (isUsingSkill1){render(renderer, skill1);}
        else if (isUsingSkill2){render(renderer, skill2);}
        else if (isUsingSkill3){render(renderer, skill3);}
        else if (isGettingDamaged){render(renderer, getDamaged);}
        else if (isGettingKilled){render(renderer, getKilled);}
        else if (isRunning){render(renderer, run);}
        else{render(renderer, idle);}
    }
}
