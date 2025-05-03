//========================Music.cpp========================

#include "Music.h"

void Music::loadSoundtrack()
{
    backgroundMusic = Mix_LoadMUS((path + "Come Along With Me" + ".mp3").c_str());
    combatMusic = Mix_LoadMUS((path + "Chip Dip Triple Flips Are Hip" + ".mp3").c_str());
    victoryMusic = Mix_LoadMUS((path + "Victory Theme" + ".mp3").c_str());
    defeatedMusic = Mix_LoadMUS((path + "Defeated Theme" + ".mp3").c_str());
}

void Music::loadSFX(string name)
{
    sfx[name] = Mix_LoadWAV((path + name + ".wav").c_str());
}

void Music::playSFX(string name, int channel)
{
    Mix_PlayChannel(channel, sfx[name], 0);
}

void Music::stopSFX(int channel)
{
    Mix_HaltChannel(channel);
}

//backgroundMusic = Mix_LoadMUS((path + "Come Along With Me" + ".mp3").c_str());
//combatMusic = Mix_LoadMUS((path + "Chip Dip Triple Flips Are Hip" + ".mp3").c_str());
//sfx["Click"] = Mix_LoadWAV((path + "Click" + ".wav").c_str());
//sfx["Switch"] = Mix_LoadWAV((path + "Switch" + ".wav").c_str());
//sfx["Sword"] = Mix_LoadWAV((path + "Sword" + ".wav").c_str());