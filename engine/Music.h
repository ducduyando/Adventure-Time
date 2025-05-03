//========================Music.cpp========================

#ifndef MUSIC_H
#define MUSIC_H

#include "SDL3/SDL.h"
#include "Constants.h"
#include "SDL3_mixer/SDL_mixer.h"
#include <string>
#include <map>

using namespace std;

class Music
{
    public:
    Mix_Music* backgroundMusic;
    Mix_Music* combatMusic;
    Mix_Music* victoryMusic;
    Mix_Music* defeatedMusic;
    map <string,Mix_Chunk*> sfx;

    void loadSoundtrack();
    void loadSFX(string name);
    void playSFX(string name, int channel);
    void stopSFX(int channel);

};

#endif //MUSIC_H
