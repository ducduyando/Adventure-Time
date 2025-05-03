//========================Game.cpp========================
#include <vector>
#include <random>
#include "Game.h"
#include "Constants.h"

Game::Game() {window = nullptr; renderer = nullptr; currentMusic = nullptr; running = true; menu = true; chooseGameMode = false; loading = false; playAgain = true; level = 0.5;}

bool Game::defaultInit()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {return false;}
    window = SDL_CreateWindow("GameProject", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!window || !renderer) {return false;}
    return true;
}

bool Game::musicInit()
{
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0){return false;}
    SDL_AudioSpec audioSpec = {MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, MIX_DEFAULT_FREQUENCY};
    if (Mix_OpenAudio(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec) < 0) {return false;}
    Mix_AllocateChannels(64);
    MUSIC.loadSoundtrack();
    MUSIC.loadSFX("Click");
    MUSIC.loadSFX("Switch");
    MUSIC.loadSFX("Sword");
    if (!MUSIC.backgroundMusic || !MUSIC.combatMusic || !MUSIC.victoryMusic) {return false;}
    return true;
}

void Game::reset()
{
    FINN.npcRespawn();SKELETON.npcRespawn();WARRIOR.npcRespawn();NINJA.npcRespawn();
    MENU.menuReset();DIFFICULTYMODE.menuReset();LOADING.menuReset();WIN.menuReset();LOSE.menuReset();
    LEVEL.levelReset();
}


bool Game::menuInit()
{
    MENU.loadMedia(renderer, "Menu", 0, 0);
    DIFFICULTYMODE.loadMedia(renderer, "DifficultyMode", 0, 0);
    LOADING.loadMedia(renderer, "Loading", 0, 0);
    WIN.loadMedia(renderer, "Win", 0, 0);
    LOSE.loadMedia(renderer, "Lose", 0, 0);
    MENU.initialize();DIFFICULTYMODE.initialize();LOADING.initialize();WIN.initialize();LOSE.initialize();
    return true;
}

bool Game::levelInit()
{
    LEVEL.loadMedia(renderer, "Level", 228, 10);
    LEVEL.initialize();
    return true;
}

bool Game::gameInit()
{
    FINN.loadMedia(renderer, "Finn", 100, 350);
    SKELETON.loadMedia(renderer, "Skeleton", 580, 350);
    WARRIOR.loadMedia(renderer, "Warrior", 564, 350);
    NINJA.loadMedia(renderer, "Ninja", 564, 350);
    BACKGROUND.loadBackground(renderer, 0, 0);
    FINN.defaultSFX();SKELETON.defaultSFX();WARRIOR.defaultSFX();NINJA.defaultSFX();
    FINN.initialize();SKELETON.initialize();WARRIOR.initialize();NINJA.initialize();
    return true;
}

void Game::menuLogic()
{
    if (menu && !chooseGameMode && !loading){updateFrame(MENU.idle, MENU.idle.frame.limit, SCREEN_WIDTH);}
    else if (!menu && chooseGameMode && !loading){updateFrame(DIFFICULTYMODE.idle, DIFFICULTYMODE.idle.frame.limit, SCREEN_WIDTH);}
    else if (!menu && !chooseGameMode && loading)
    {
        if (LOADING.idle.frame.currentFrame < LOADING.idle.frame.limit - 1){updateFrame(LOADING.idle, LOADING.idle.frame.limit, SCREEN_WIDTH);}
        else
        {
            SDL_Delay(LOADING.idle.frame.delay);
            loading = false;
        }
    }
}

void Game::levelLogic()
{
    //updateFrame(LEVEL.idle, LEVEL.idle.frame.limit, LEVEL_WIDTH);
    if (level == 0.5){if (LEVEL.idle.frame.currentFrame < 0){updateFrame(LEVEL.idle, LEVEL.idle.frame.limit, LEVEL_WIDTH);}}
    if (level == 1.5){if (LEVEL.idle.frame.currentFrame < 4){updateFrame(LEVEL.idle, LEVEL.idle.frame.limit, LEVEL_WIDTH);}}
    if (level == 2.5){if (LEVEL.idle.frame.currentFrame < 8){updateFrame(LEVEL.idle, LEVEL.idle.frame.limit, LEVEL_WIDTH);}}
    if (level == 3.5){if (LEVEL.idle.frame.currentFrame < 12){updateFrame(LEVEL.idle, LEVEL.idle.frame.limit, LEVEL_WIDTH);}}
}

void Game::gameLogic()
{
    if (level == 0.5)
    {
        if (FINN.isRunning)
        {
            FINN.systemPlay("Run");
            if (FINN.run.frame.currentFrame < FINN.run.frame.limit - 1){updateFrame(FINN.run, FINN.run.frame.limit, SPRITE_WIDTH);BACKGROUND.updateBackground();}
            else{SDL_Delay(FINN.run.frame.delay);FINN.isRunning = false;FINN.run.frame.currentFrame = 0;SKELETON.isRunning = true;level = 1;}
        }
    }
    if (level == 1 || level == 1.5)
    {
        if (!FINN.isDead)
        {
            updateFrame(FINN.idle, FINN.idle.frame.limit, SPRITE_WIDTH);
            if (FINN.energyBar.frame.currentFrame < FINN.energyBar.frame.limit - 1 && !FINN.isRunning && !SKELETON.isRunning) {updateFrame(FINN.energyBar, FINN.energyBar.frame.limit, BAR_WIDTH);}
        }
        if (FINN.isUsingSkill1)
        {
            if (FINN.skill1.frame.currentFrame < FINN.skill1.frame.limit - 1){updateFrame(FINN.skill1, FINN.skill1.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(FINN.skill1.frame.delay);
                FINN.isUsingSkill1 = false;
                if (!SKELETON.isUsingSkill3){SKELETON.takeDamage(2);}
                else
                {
                    FINN.systemPlay("Shield block");
                    SKELETON.shieldCancel();
                    if (FINN.isUsingSkill2){FINN.shieldCancel();}
                    else{FINN.takeDamage(1);}
                }
            }
        }
        if (FINN.isUsingSkill2)
        {
            if (FINN.skill2.frame.currentFrame < FINN.skill2.frame.limit - 1 && FINN.skill2.frame.currentFrame >= 0){updateFrame(FINN.skill2, FINN.skill2.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(FINN.skill2.frame.delay);FINN.isUsingSkill2 = false;}
        }
        if (!FINN.isUsingSkill2)
        {
            FINN.skill2.frame.currentFrame = -2;
            updateFrame(FINN.skill2, FINN.skill2.frame.limit, SPRITE_WIDTH);
        }
        if (FINN.isUsingSkill3)
        {
            if (FINN.skill3.frame.currentFrame < FINN.skill3.frame.limit - 1){updateFrame(FINN.skill3, FINN.skill3.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(FINN.skill3.frame.delay);
                FINN.isUsingSkill3 = false;
                if (!SKELETON.isUsingSkill3){SKELETON.takeDamage(3);FINN.heal(1);}
                else
                {
                    FINN.systemPlay("Shield block");
                    SKELETON.shieldCancel();
                    if (FINN.isUsingSkill2){FINN.shieldCancel();}
                    else{FINN.takeDamage(1);}
                }
            }
        }
        if (FINN.isGettingDamaged)
        {
            FINN.music.stopSFX(FINN.channel["Charge up"]);
            FINN.systemPlay("Get hit");
            FINN.isUsingSkill3 = false;
            if (FINN.getDamaged.frame.currentFrame < FINN.getDamaged.frame.limit - 1){updateFrame(FINN.getDamaged, FINN.getDamaged.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(FINN.getDamaged.frame.delay);FINN.isGettingDamaged = false;}
        }
        if (FINN.isRunning)
        {
            FINN.systemPlay("Run");
            if (FINN.run.frame.currentFrame < FINN.run.frame.limit - 1){updateFrame(FINN.run, FINN.run.frame.limit, SPRITE_WIDTH);BACKGROUND.updateBackground();}
            else{SDL_Delay(FINN.run.frame.delay);FINN.isRunning = false;FINN.run.frame.currentFrame = 0;WARRIOR.isRunning = true;level = 2;FINN.reset();WARRIOR.reset();}
        }
        if (FINN.isGettingKilled)
        {
            playMusic(MUSIC.defeatedMusic);
            if (FINN.getKilled.frame.currentFrame < SKELETON.getKilled.frame.limit - 1){updateFrame(FINN.getKilled, FINN.getKilled.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(SKELETON.getKilled.frame.delay);SKELETON.isGettingKilled = false;level = 4.5;FINN.isDead = true;}
        }

        if (!SKELETON.isDead)
        {
            updateFrame(SKELETON.idle, SKELETON.idle.frame.limit, SPRITE_WIDTH);
            if (SKELETON.energyBar.frame.currentFrame < SKELETON.energyBar.frame.limit - 1 && !FINN.isRunning && !SKELETON.isRunning) {updateFrame(SKELETON.energyBar, SKELETON.energyBar.frame.limit, BAR_WIDTH);}
        }
        if (SKELETON.isUsingSkill1)
        {
            if (SKELETON.skill1.frame.currentFrame < SKELETON.skill1.frame.limit - 1){updateFrame(SKELETON.skill1, SKELETON.skill1.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(SKELETON.skill1.frame.delay);
                SKELETON.isUsingSkill1 = false;
                if (!FINN.isUsingSkill2)
                {
                    FINN.takeDamage(2);
                }
                FINN.shieldCancel();
            }
        }
        if (SKELETON.isUsingSkill2)
        {
            if (SKELETON.skill2.frame.currentFrame < SKELETON.skill2.frame.limit - 1){updateFrame(SKELETON.skill2, SKELETON.skill2.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(SKELETON.skill2.frame.delay);
                if (SKELETON.skeletonArrows > 0)
                {
                    if (!FINN.isUsingSkill2){FINN.takeDamage(1);}
                    FINN.shieldCancel();
                    if (SKELETON.skeletonArrows != 1){SKELETON.skill2.frame.currentFrame = 0;}
                    SKELETON.skeletonArrows--;
                    if (SKELETON.skeletonArrows == 0){SKELETON.isUsingSkill2 = false;}
                }
            }
        }
        if (SKELETON.isUsingSkill3)
        {
            if (SKELETON.skill3.frame.currentFrame < SKELETON.skill3.frame.limit - 1){updateFrame(SKELETON.skill3, SKELETON.skill3.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(SKELETON.skill3.frame.delay);
                SKELETON.isUsingSkill3 = false;
            }
        }
        if (SKELETON.isGettingDamaged)
        {
            SKELETON.music.stopSFX(SKELETON.channel["Bow"]);
            SKELETON.systemPlay("Get hit");
            SKELETON.isUsingSkill2 = false;
            if (SKELETON.getDamaged.frame.currentFrame < SKELETON.getDamaged.frame.limit - 1){updateFrame(SKELETON.getDamaged, SKELETON.getDamaged.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(SKELETON.getDamaged.frame.delay);SKELETON.isGettingDamaged = false;}
        }
        if (SKELETON.isRunning)
        {
            SKELETON.systemPlay("Run");
            if (SKELETON.run.frame.currentFrame < SKELETON.run.frame.limit - 1){move(SKELETON.run, 580, SKELETON.run.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(SKELETON.run.frame.delay);SKELETON.isRunning = false;}
        }
        if (SKELETON.isGettingKilled)
        {
            FINN.systemPlay("Stage win");
            if (SKELETON.getKilled.frame.currentFrame < SKELETON.getKilled.frame.limit - 1){updateFrame(SKELETON.getKilled, SKELETON.getKilled.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(SKELETON.getKilled.frame.delay);SKELETON.isGettingKilled = false;level = 1.5;SKELETON.isDead = true;FINN.isRunning = true;}
        }
    }
    if (level == 2 || level == 2.5)
    {
        if (!FINN.isDead)
        {
            updateFrame(FINN.idle, FINN.idle.frame.limit, SPRITE_WIDTH);
            if (FINN.energyBar.frame.currentFrame < FINN.energyBar.frame.limit - 1 && !FINN.isRunning && !WARRIOR.isRunning) {updateFrame(FINN.energyBar, FINN.energyBar.frame.limit, BAR_WIDTH);}
        }
        if (FINN.isUsingSkill1)
        {
            if (FINN.skill1.frame.currentFrame < FINN.skill1.frame.limit - 1){updateFrame(FINN.skill1, FINN.skill1.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(FINN.skill1.frame.delay);
                FINN.isUsingSkill1 = false;
                if (!WARRIOR.isUsingSkill3){WARRIOR.takeDamage(2);}
                else{WARRIOR.shieldCancel();FINN.systemPlay("Shield block");}
            }
        }
        if (FINN.isUsingSkill2)
        {
            if (FINN.skill2.frame.currentFrame < FINN.skill2.frame.limit - 1 && FINN.skill2.frame.currentFrame >= 0){updateFrame(FINN.skill2, FINN.skill2.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(FINN.skill2.frame.delay);FINN.isUsingSkill2 = false;}
        }
        if (!FINN.isUsingSkill2)
        {
            FINN.skill2.frame.currentFrame = -2;
            updateFrame(FINN.skill2, FINN.skill2.frame.limit, SPRITE_WIDTH);
        }
        if (FINN.isUsingSkill3)
        {
            if (FINN.skill3.frame.currentFrame < FINN.skill3.frame.limit - 1){updateFrame(FINN.skill3, FINN.skill3.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(FINN.skill3.frame.delay);
                FINN.isUsingSkill3 = false;
                if (!WARRIOR.isUsingSkill3){WARRIOR.takeDamage(3);FINN.heal(1);}
                else{WARRIOR.shieldCancel();FINN.systemPlay("Shield block");}
            }
        }
        if (FINN.isGettingDamaged)
        {
            FINN.music.stopSFX(FINN.channel["Charge up"]);
            FINN.systemPlay("Get hit");
            FINN.isUsingSkill3 = false;
            if (FINN.getDamaged.frame.currentFrame < FINN.getDamaged.frame.limit - 1){updateFrame(FINN.getDamaged, FINN.getDamaged.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(FINN.getDamaged.frame.delay);FINN.isGettingDamaged = false;}
        }
        if (FINN.isRunning)
        {
            FINN.systemPlay("Run");
            if (FINN.run.frame.currentFrame < FINN.run.frame.limit - 1){updateFrame(FINN.run, FINN.run.frame.limit, SPRITE_WIDTH);BACKGROUND.updateBackground();}
            else{SDL_Delay(FINN.run.frame.delay);FINN.isRunning = false;FINN.run.frame.currentFrame = 0;NINJA.isRunning = true;level = 3;FINN.reset();NINJA.reset();}
        }
        if (FINN.isGettingKilled)
        {
            playMusic(MUSIC.defeatedMusic);
            if (FINN.getKilled.frame.currentFrame < SKELETON.getKilled.frame.limit - 1){updateFrame(FINN.getKilled, FINN.getKilled.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(SKELETON.getKilled.frame.delay);SKELETON.isGettingKilled = false;level = 4.5;FINN.isDead = true;}
        }

        if (!WARRIOR.isDead)
        {
            updateFrame(WARRIOR.idle, WARRIOR.idle.frame.limit, SPRITE_WIDTH);
            if (WARRIOR.energyBar.frame.currentFrame < WARRIOR.energyBar.frame.limit - 1 && !FINN.isRunning && !WARRIOR.isRunning) {updateFrame(WARRIOR.energyBar, WARRIOR.energyBar.frame.limit, BAR_WIDTH);}
        }
        if (WARRIOR.isUsingSkill1)
        {
            if (WARRIOR.skill1.frame.currentFrame < WARRIOR.skill1.frame.limit - 1){updateFrame(WARRIOR.skill1, WARRIOR.skill1.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(WARRIOR.skill1.frame.delay);
                WARRIOR.isUsingSkill1 = false;
                if (!FINN.isUsingSkill2){FINN.takeDamage(2);}
                else{FINN.shieldCancel();FINN.takeDamage(1);}
            }
        }
        if (WARRIOR.isUsingSkill2)
        {
            if (WARRIOR.skill2.frame.currentFrame == 0 && WARRIOR.checkHp){WARRIOR.heal(1);WARRIOR.checkHp = false;}
            if (WARRIOR.skill2.frame.currentFrame < WARRIOR.skill2.frame.limit - 1){updateFrame(WARRIOR.skill2, WARRIOR.skill2.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(WARRIOR.skill2.frame.delay);WARRIOR.isUsingSkill2 = false;WARRIOR.heal(1);WARRIOR.checkHp = true;}
        }
        if (WARRIOR.isUsingSkill3)
        {
            if (WARRIOR.skill3.frame.currentFrame == 8 && WARRIOR.checkHit){if(FINN.isUsingSkill2){FINN.shieldCancel();}else{FINN.takeDamage(1);};WARRIOR.checkHit = false;}
            if (WARRIOR.skill3.frame.currentFrame < WARRIOR.skill3.frame.limit - 1){updateFrame(WARRIOR.skill3, WARRIOR.skill3.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(WARRIOR.skill3.frame.delay);WARRIOR.isUsingSkill3 = false;WARRIOR.checkHit = true;}
        }
        if (WARRIOR.isGettingDamaged)
        {
            WARRIOR.music.stopSFX(WARRIOR.channel["Hp up"]);
            WARRIOR.systemPlay("Get hit");
            WARRIOR.isUsingSkill2 = false;
            if (WARRIOR.getDamaged.frame.currentFrame < WARRIOR.getDamaged.frame.limit - 1){updateFrame(WARRIOR.getDamaged, WARRIOR.getDamaged.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(WARRIOR.getDamaged.frame.delay);WARRIOR.isGettingDamaged = false;}
        }
        if (WARRIOR.isRunning)
        {
            WARRIOR.systemPlay("Run");
            if (WARRIOR.run.frame.currentFrame < WARRIOR.run.frame.limit - 1){move(WARRIOR.run, 580, WARRIOR.run.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(WARRIOR.run.frame.delay);WARRIOR.isRunning = false;}
        }
        if (WARRIOR.isGettingKilled)
        {
            FINN.systemPlay("Stage win");
            if (WARRIOR.getKilled.frame.currentFrame < WARRIOR.getKilled.frame.limit - 1){updateFrame(WARRIOR.getKilled, WARRIOR.getKilled.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(WARRIOR.getKilled.frame.delay);WARRIOR.isGettingKilled = false;level = 2.5;WARRIOR.isDead = true;FINN.isRunning = true;}
        }
    }

    if (level == 3 || level == 3.5)
    {
        if (!FINN.isDead)
        {
            updateFrame(FINN.idle, FINN.idle.frame.limit, SPRITE_WIDTH);
            if (FINN.energyBar.frame.currentFrame < FINN.energyBar.frame.limit - 1 && !FINN.isRunning && !NINJA.isRunning) {updateFrame(FINN.energyBar, FINN.energyBar.frame.limit, BAR_WIDTH);}
        }
        if (FINN.isUsingSkill1)
        {
            if (FINN.skill1.frame.currentFrame < FINN.skill1.frame.limit - 1){updateFrame(FINN.skill1, FINN.skill1.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(FINN.skill1.frame.delay);
                FINN.isUsingSkill1 = false;
                if (!NINJA.isUsingSkill3 && !NINJA.isCloning){NINJA.takeDamage(2);}
                else
                {
                    NINJA.cloneCancel();
                    NINJA.usingClone();
                    NINJA.takeDamage(1);
                }
            }
        }
        if (FINN.isUsingSkill2)
        {
            if (FINN.skill2.frame.currentFrame < FINN.skill2.frame.limit - 1 && FINN.skill2.frame.currentFrame >= 0){updateFrame(FINN.skill2, FINN.skill2.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(FINN.skill2.frame.delay);FINN.isUsingSkill2 = false;}
        }
        if (!FINN.isUsingSkill2)
        {
            FINN.skill2.frame.currentFrame = -2;
            updateFrame(FINN.skill2, FINN.skill2.frame.limit, SPRITE_WIDTH);
        }
        if (FINN.isUsingSkill3)
        {
            if (FINN.skill3.frame.currentFrame < FINN.skill3.frame.limit - 1){updateFrame(FINN.skill3, FINN.skill3.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(FINN.skill3.frame.delay);
                FINN.isUsingSkill3 = false;
                if (!NINJA.isUsingSkill3 && !NINJA.isCloning){NINJA.takeDamage(3);FINN.heal(1);}
                else
                {
                    NINJA.cloneCancel();
                    NINJA.usingClone();
                    NINJA.takeDamage(2);
                    FINN.heal(1);
                }
            }
        }
        if (FINN.isGettingDamaged)
        {
            FINN.systemPlay("Get hit");
            FINN.isUsingSkill3 = false;
            if (FINN.getDamaged.frame.currentFrame < FINN.getDamaged.frame.limit - 1){updateFrame(FINN.getDamaged, FINN.getDamaged.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(FINN.getDamaged.frame.delay);FINN.isGettingDamaged = false;}
        }
        if (FINN.isRunning)
        {
            FINN.systemPlay("Run");
            if (FINN.run.frame.currentFrame < FINN.run.frame.limit - 1){updateFrame(FINN.run, FINN.run.frame.limit, SPRITE_WIDTH);BACKGROUND.updateBackground();}
            else{SDL_Delay(FINN.run.frame.delay);FINN.isRunning = false;FINN.run.frame.currentFrame = 0;level = 4;FINN.reset();}
        }
        if (FINN.isGettingKilled)
        {
            playMusic(MUSIC.defeatedMusic);
            if (FINN.getKilled.frame.currentFrame < SKELETON.getKilled.frame.limit - 1){updateFrame(FINN.getKilled, FINN.getKilled.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(SKELETON.getKilled.frame.delay);SKELETON.isGettingKilled = false;level = 4.5;FINN.isDead = true;}
        }

        if (!NINJA.isDead)
        {
            updateFrame(NINJA.idle, NINJA.idle.frame.limit, SPRITE_WIDTH);
            if (NINJA.energyBar.frame.currentFrame < NINJA.energyBar.frame.limit - 1 && !FINN.isRunning && !NINJA.isRunning) {updateFrame(NINJA.energyBar, NINJA.energyBar.frame.limit, BAR_WIDTH);}
        }
        if (NINJA.isUsingSkill1)
        {
            if (NINJA.skill1.frame.currentFrame < NINJA.skill1.frame.limit - 1){updateFrame(NINJA.skill1, NINJA.skill1.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(NINJA.skill1.frame.delay);
                NINJA.isUsingSkill1 = false;
                if (FINN.isUsingSkill2)
                {
                    FINN.takeDamage(1);
                    NINJA.heal(1);
                }
                else
                {
                    FINN.takeDamage(2);
                    NINJA.heal(2);
                }
                if (NINJA.isCloning)
                {
                    FINN.takeDamage(1);
                    NINJA.heal(1);
                }
                FINN.shieldCancel();
            }
        }
        if (NINJA.isUsingSkill2)
        {
            if (NINJA.skill2.frame.currentFrame < NINJA.skill2.frame.limit - 1){updateFrame(NINJA.skill2, NINJA.skill2.frame.limit, SPRITE_WIDTH);}
            else
            {
                SDL_Delay(NINJA.skill2.frame.delay);
                if (NINJA.ninjaShurikens > 0)
                {
                    if (!FINN.isUsingSkill2){FINN.takeDamage(2);if (NINJA.isCloning){FINN.takeDamage(1);}}
                    else{FINN.shieldCancel();}
                    if (NINJA.ninjaShurikens != 1){NINJA.skill2.frame.currentFrame = 0;}
                    NINJA.ninjaShurikens--;
                    if (NINJA.ninjaShurikens == 0){NINJA.isUsingSkill2 = false;}
                }
            }
        }
        if (NINJA.isUsingSkill3)
        {
            if (NINJA.skill3.frame.currentFrame < NINJA.skill3.frame.limit - 1){updateFrame(NINJA.skill3, NINJA.skill3.frame.limit, SPRITE_WIDTH);updateLayer(SKELETON.run, 1);}
            else
            {
                SDL_Delay(NINJA.skill3.frame.delay);
                NINJA.isUsingSkill3 = false;
                NINJA.isCloning = true;
                NINJA.usingClone();
            }
        }
        if (NINJA.isGettingDamaged)
        {
            NINJA.music.stopSFX(WARRIOR.channel["Shuriken"]);
            NINJA.music.stopSFX(WARRIOR.channel["Shadow clone"]);
            NINJA.systemPlay("Get hit");
            NINJA.isUsingSkill2 = false;
            if (NINJA.getDamaged.frame.currentFrame < NINJA.getDamaged.frame.limit - 1){updateFrame(NINJA.getDamaged, NINJA.getDamaged.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(NINJA.getDamaged.frame.delay);NINJA.isGettingDamaged = false;}
        }
        if (NINJA.isRunning)
        {
            NINJA.systemPlay("Run");
            if (NINJA.run.frame.currentFrame < NINJA.run.frame.limit - 1){move(NINJA.run, 580, NINJA.run.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(NINJA.run.frame.delay);NINJA.isRunning = false;}
        }
        if (NINJA.isGettingKilled)
        {
            FINN.systemPlay("Stage win");
            if (NINJA.getKilled.frame.currentFrame < NINJA.getKilled.frame.limit - 1){updateFrame(NINJA.getKilled, NINJA.getKilled.frame.limit, SPRITE_WIDTH);}
            else{SDL_Delay(NINJA.getKilled.frame.delay);NINJA.isGettingKilled = false;level = 3.5;NINJA.isDead = true;FINN.isRunning = true;}
        }
    }
    if (level == 4)
    {
        if (WIN.idle.frame.currentFrame < WIN.idle.frame.limit - 1){updateFrame(WIN.idle, WIN.idle.frame.limit, SCREEN_WIDTH);}
        else{SDL_Delay(WIN.idle.frame.delay);menu = true;}
    }
    if (level == 4.5)
    {
        if (LOSE.idle.frame.currentFrame < LOSE.idle.frame.limit - 1){updateFrame(LOSE.idle, LOSE.idle.frame.limit, SCREEN_WIDTH);}
        else{SDL_Delay(LOSE.idle.frame.delay);menu = true;}
    }
}


void Game::gameHandle(SDL_Event& e)
{
    if (e.type == SDL_EVENT_QUIT){running =false;}
    if (e.type == SDL_EVENT_KEY_DOWN)
    {
        auto keyInput = e.key.key;
        if (chooseGameMode)
        {
            if (keyInput == SDLK_LEFT || keyInput == SDLK_RIGHT || keyInput == SDLK_UP || keyInput == SDLK_DOWN){MUSIC.playSFX("Switch", SYSTEM_CHANNEL);moveArrow(DIFFICULTYMODE.idle);}
            if (keyInput == SDLK_RETURN)
            {
                MUSIC.playSFX("Click", SYSTEM_CHANNEL);
                if (DIFFICULTYMODE.gameStart()){gameMode = "Easy";}
                else{gameMode = "Hard";}
                chooseGameMode = false;loading = true;reset();FINN.isRunning = true;FINN.run.rect.x = 100;level = 0.5;
            }
        }
        if (menu)
        {
            if (keyInput == SDLK_LEFT || keyInput == SDLK_RIGHT || keyInput == SDLK_UP || keyInput == SDLK_DOWN){MUSIC.playSFX("Switch", SYSTEM_CHANNEL);moveArrow(MENU.idle);}
            if (keyInput == SDLK_RETURN)
            {
                MUSIC.playSFX("Click", SYSTEM_CHANNEL);
                if (MENU.gameStart()){menu = false;chooseGameMode = true;}
                else{running = false;}
            }
        }

        if (keyInput == SDLK_1){FINN.useSkill1();}
        if (keyInput == SDLK_2){FINN.useSkill2();}
        if (keyInput == SDLK_3){FINN.useSkill3();}
    }

}



void Game::randomSkillEasy(int delay)
{
    Uint32 startTime = SDL_GetTicks();
    if (startTime%delay == 0)
    {
        int randomNumber = (level-1)*3 + random() % 3;
        switch (randomNumber)
        {
        case 0: SKELETON.useSkill1();break;
        case 1: SKELETON.useSkill2();break;
        case 2: SKELETON.useSkill3();break;
        case 3: WARRIOR.useSkill1();break;
        case 4: WARRIOR.useSkill2();break;
        case 5: WARRIOR.useSkill3();break;
        case 6: NINJA.useSkill1();break;
        case 7: NINJA.useSkill2();break;
        case 8: NINJA.useSkill3();break;
        }
    }
}

void Game::randomSkillHard(int delay)
{
    Uint32 startTime = SDL_GetTicks();
    if (level == 1)
    {
        if (startTime%delay == 0)
        {
            if (SKELETON.isUsingSkill3)
            {
                int randomNumber = random() % 2;
                switch (randomNumber)
                {
                    case 0: SKELETON.useSkill1();break;
                    case 1: SKELETON.useSkill2();break;
                }
            }
            else
            {
                int randomNumber = random() % 3;
                switch (randomNumber)
                {
                    case 0: SKELETON.useSkill1();break;
                    case 1: SKELETON.useSkill2();break;
                    case 2: SKELETON.useSkill3();break;
                }
            }
        }
    }
    if (level == 2)
    {
        if (startTime%(delay/2) == 0)
        {
            if (WARRIOR.isUsingSkill2 || WARRIOR.healthBar.frame.currentFrame == 0 || WARRIOR.healthBar.frame.currentFrame == 1)
            {
                int randomNumber = random() % 2;
                switch (randomNumber)
                {
                    case 0: WARRIOR.useSkill1();break;
                    case 1: WARRIOR.useSkill3();break;
                }
            }
            if (WARRIOR.isUsingSkill3)
            {
                int randomNumber = random() % 2;
                switch (randomNumber)
                {
                    case 0: WARRIOR.useSkill1();break;
                    case 1: WARRIOR.useSkill2();break;
                }
            }
        }
    }
    if (level == 3)
    {
        if (!NINJA.isCloning)
        {
            if (FINN.isUsingSkill1){NINJA.useSkill1();}
            else if (FINN.isUsingSkill2)
            {
                int randomNumber = random() % 2;
                switch (randomNumber)
                {
                case 0: NINJA.useSkill3();break;
                case 1: NINJA.useSkill2();break;
                }
            }
            else if (FINN.isUsingSkill3)
            {
                int randomNumber = random() % 2;
                switch (randomNumber)
                {
                case 0: NINJA.useSkill1();break;
                case 1: NINJA.useSkill2();break;
                }
            }
        }
        else
        {
            int randomNumber = random() % 2;
            switch (randomNumber)
            {
            case 0: NINJA.useSkill1();break;
            case 1: NINJA.useSkill2();break;
            }
        }
    }
}

void Game::playMusic(Mix_Music* musicToPlay)
{
    if (currentMusic != musicToPlay)
    {
        Mix_HaltMusic();
        Mix_PlayMusic(musicToPlay, -1);
        currentMusic = musicToPlay;
    }
}


void Game::defaultRender()
{
    SDL_RenderClear(renderer);
    if (menu && !chooseGameMode && !loading){MENU.renderLogic(renderer);}
    else if (!menu && chooseGameMode && !loading){DIFFICULTYMODE.renderLogic(renderer);}
    else if (!menu && !chooseGameMode && loading){LOADING.renderLogic(renderer);}
    else
    {
        BACKGROUND.renderLogic(renderer);
        LEVEL.renderLogic(renderer);
        FINN.renderLogic(renderer);
        if (level == 1){SKELETON.renderLogic(renderer);}
        if (level == 2){WARRIOR.renderLogic(renderer);}
        if (level == 3){NINJA.renderLogic(renderer);}
        if (level == 4){WIN.renderLogic(renderer);}
        if (level == 4.5){LOSE.renderLogic(renderer);}
    }
    SDL_RenderPresent(renderer);
}


void Game::run()
{
    SDL_Event e;
    playMusic(MUSIC.backgroundMusic);
    while (running)
    {
        while (SDL_PollEvent(&e)){gameHandle(e);}
        if (menu||chooseGameMode||loading){playMusic(MUSIC.backgroundMusic);menuLogic();}
        else
        {
            if (level == 4){playMusic(MUSIC.victoryMusic);}
            else if (level == 4.5){playMusic(MUSIC.defeatedMusic);}
            else{playMusic(MUSIC.combatMusic);}
            gameLogic();levelLogic();
            if (gameMode == "Easy"){randomSkillEasy(300);}
            else if (gameMode == "Hard"){randomSkillHard(250);}
        }
        defaultRender();
        SDL_Delay(16);
    }
}

void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    Mix_Quit();
}