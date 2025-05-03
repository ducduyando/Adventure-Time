//========================Skeleton.cpp========================


#include <iostream>
using namespace std;

#include "Character.h"
#include "Skeleton.h"

void Skeleton::initialize()
{
    channel["Get hit"] = 10;
    channel["Run"] = 11;
    music.loadSFX("Dead");channel["Dead"] = 12;
    music.loadSFX("Sword");channel["Sword"] = 13;
    music.loadSFX("Bow");channel["Bow"] = 14;
    music.loadSFX("Shield up");channel["Shield up"] = 15;
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
    skeletonArrows = 3;
}

void Skeleton::useSkill1()
{
    if (!isUsingSkill1 && !isUsingSkill2 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Sword", channel["Sword"]);
        isUsingSkill1 = true;
        skill1.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Skeleton::useSkill2()
{
    if (!isUsingSkill1 && !isUsingSkill2 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 2)
    {
        music.playSFX("Bow", channel["Bow"]);
        skeletonArrows = 3;
        isUsingSkill2 = true;
        skill2.frame.currentFrame = 0;
        loseMana(2);
    }
}

void Skeleton::useSkill3()
{
    if (!isUsingSkill1 && !isUsingSkill2 && !isUsingSkill3 && !isGettingDamaged && energyBar.frame.currentFrame >= 3)
    {
        music.playSFX("Shield up", channel["Shield up"]);
        isUsingSkill3 = true;
        skill3.frame.currentFrame = 0;
        loseMana(3);
    }
}

void Skeleton::shieldCancel()
{
    isUsingSkill3 = false;
}

void Skeleton::render(SDL_Renderer* renderer, Texture tex)
{
    SDL_RenderTexture(renderer, tex.texture, &tex.clip, &tex.rect);
}

void Skeleton::renderLogic(SDL_Renderer* renderer)
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
