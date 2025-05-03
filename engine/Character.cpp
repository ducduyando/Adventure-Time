//========================Character.cpp========================

#include "Character.h"

void Character::loadMedia(SDL_Renderer* renderer, const string name, float x, float y)
{
    if (name == "Menu" || name == "DifficultyMode" || name == "Win" || name == "Lose"){idle = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+name+".png").c_str()), {0, 0, SPRITE_DELAY*3}, {idle.frame.currentFrame*SCREEN_WIDTH, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};}
    else if (name == "Loading"){idle = {{x, y, SCREEN_WIDTH, SCREEN_HEIGHT}, loadTexture(renderer, (path+name+".png").c_str()), {0, 0, SPRITE_DELAY*2}, {idle.frame.currentFrame*SCREEN_WIDTH, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT}};}
    else if (name == "Level"){idle = {{x, y, LEVEL_WIDTH/2, LEVEL_HEIGHT/2}, loadTexture(renderer, (path+name+".png").c_str()), {0, 0, SPRITE_DELAY*6}, {idle.frame.currentFrame*LEVEL_WIDTH, 0.0f, LEVEL_WIDTH, LEVEL_HEIGHT}};}
    else
    {
        idle = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"Idle.png").c_str()), {0, 0, SPRITE_DELAY}, {idle.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};
        if (name == "Finn")
        {
            healthBar = {{30, 530, BAR_WIDTH/2, BAR_HEIGHT/2}, loadTexture(renderer, (path+"HealthBar.png").c_str()),{0, 0, }, {healthBar.frame.currentFrame*BAR_WIDTH, 0.0f, BAR_WIDTH, BAR_HEIGHT}};
            energyBar = {{30, 490, BAR_WIDTH/2, BAR_HEIGHT/2}, loadTexture(renderer, (path+"EnergyBar.png").c_str()), {0, 0, ENERGYBAR_DELAY}, {energyBar.frame.currentFrame*BAR_WIDTH, 0.0f, BAR_WIDTH, BAR_HEIGHT}};
        }
        else
        {
            healthBar = {{510, 530, BAR_WIDTH/2, BAR_HEIGHT/2}, loadTexture(renderer, (path+"HealthBar.png").c_str()),{0, 0, }, {healthBar.frame.currentFrame*BAR_WIDTH, 0.0f, BAR_WIDTH, BAR_HEIGHT}};
            energyBar = {{510, 490, BAR_WIDTH/2, BAR_HEIGHT/2}, loadTexture(renderer, (path+"EnergyBar.png").c_str()), {0, 0, ENERGYBAR_DELAY}, {energyBar.frame.currentFrame*BAR_WIDTH, 0.0f, BAR_WIDTH, BAR_HEIGHT}};
        }
        skill1 = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"Skill1.png").c_str()), {0, 0, SPRITE_DELAY}, {skill1.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};
        skill2 = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"Skill2.png").c_str()), {0, 0, SPRITE_DELAY}, {skill2.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};
        skill3 = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"Skill3.png").c_str()), {0, 0, SPRITE_DELAY}, {skill3.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};
        if (name == "Warrior")
        {
            getDamaged = {{x, y-16, SPRITE_WIDTH, SPRITE_HEIGHT+16}, loadTexture(renderer, (path+name+"GetDamaged.png").c_str()), {0, 0, SPRITE_DELAY}, {getDamaged.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT+16}};
            getKilled = {{x, y-16, SPRITE_WIDTH, SPRITE_HEIGHT+16}, loadTexture(renderer, (path+name+"GetKilled.png").c_str()), {0, 0, SPRITE_DELAY}, {getKilled.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT+16}};
        }
        else
        {
            getDamaged = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"GetDamaged.png").c_str()), {0, 0, SPRITE_DELAY}, {getDamaged.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};
            getKilled = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"GetKilled.png").c_str()), {0, 0, SPRITE_DELAY}, {getKilled.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};
        }
        if (name == "Finn"){run = {{x, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"Run.png").c_str()), {0, 0, SPRITE_DELAY}, {getDamaged.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};}
        else{run = {{800, y, SPRITE_WIDTH, SPRITE_HEIGHT}, loadTexture(renderer, (path+name+"Run.png").c_str()), {0, 0, SPRITE_DELAY}, {getDamaged.frame.currentFrame*SPRITE_WIDTH, 0.0f, SPRITE_WIDTH, SPRITE_HEIGHT}};}

    }
}

void Character::defaultSFX()
{
    music.loadSFX("Get hit");
    music.loadSFX("Run");
}

void Character::systemPlay(string name)
{
    if (!Mix_Playing(channel[name])){music.playSFX(name, channel[name]);}
}


void Character::takeDamage(float amount)
{
    healthBar.frame.currentFrame += amount;
    if (healthBar.frame.currentFrame >= 8)
    {
        healthBar.frame.currentFrame = 8;
        die();
        getKilled.frame.currentFrame = 0;
    }
    else
    {
        isGettingDamaged = true;
        getDamaged.frame.currentFrame = 0;
    }
    healthBar.clip.x = healthBar.frame.currentFrame * BAR_WIDTH;
}

void Character::heal(float amount)
{
    healthBar.frame.currentFrame -= amount;
    if (healthBar.frame.currentFrame <= 0){healthBar.frame.currentFrame = 0;}
    healthBar.clip.x = healthBar.frame.currentFrame * BAR_WIDTH;
}

void Character::loseMana(float amount)
{
    energyBar.frame.currentFrame -= amount;
}

void Character::reset()
{
    energyBar.frame.currentFrame = 0;
    energyBar.clip.x = energyBar.frame.currentFrame * BAR_WIDTH;
    healthBar.frame.currentFrame = 0;
    healthBar.clip.x = healthBar.frame.currentFrame * BAR_WIDTH;
}

void Character::die()
{
    isGettingKilled = true;
    isUsingSkill1 = false;
    isUsingSkill2 = false;
    isUsingSkill3 = false;
    isGettingDamaged = false;
    energyBar.frame.currentFrame = -2;
    energyBar.clip.x = energyBar.frame.currentFrame * BAR_WIDTH;
    healthBar.frame.currentFrame = -1;
    healthBar.clip.x = healthBar.frame.currentFrame * BAR_WIDTH;
}

void Character::npcRespawn()
{
    isUsingSkill1 = false;
    isUsingSkill2 = false;
    isUsingSkill3 = false;
    isGettingDamaged = false;
    isGettingKilled = false;
    isDead = false;
    isRunning = false;
    idle.frame.currentFrame = 0;
    idle.clip.x = idle.frame.currentFrame * SPRITE_WIDTH;
    healthBar.frame.currentFrame = 0;
    healthBar.clip.x = healthBar.frame.currentFrame * BAR_WIDTH;
    energyBar.frame.currentFrame = 0;
    energyBar.clip.x = energyBar.frame.currentFrame * BAR_WIDTH;
    skill1.frame.currentFrame = 0;
    skill1.clip.x = skill1.frame.currentFrame * SPRITE_WIDTH;
    skill2.frame.currentFrame = 0;
    skill2.clip.x = skill2.frame.currentFrame * SPRITE_WIDTH;
    skill3.frame.currentFrame = 0;
    skill3.clip.x = skill3.frame.currentFrame * SPRITE_WIDTH;
    getDamaged.frame.currentFrame = 0;
    getDamaged.clip.x = getDamaged.frame.currentFrame * SPRITE_WIDTH;
    getKilled.frame.currentFrame = 0;
    getKilled.clip.x = getKilled.frame.currentFrame * SPRITE_WIDTH;
    run.frame.currentFrame = 0;
    run.clip.x = run.frame.currentFrame * SPRITE_WIDTH;
    run.rect.x = SCREEN_WIDTH;
}
