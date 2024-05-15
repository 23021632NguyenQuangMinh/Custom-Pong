#ifndef _sound__H_
#define _sound__H_
#include "globalValue.h"

void initSound(){

    Mix_Init(MIX_INIT_MP3);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer co van de! SDL_mixer Error:", Mix_GetError();
        return;
    }
    scoreSound = Mix_LoadWAV("audio/updatescore.mp3");
    wallHitSound = Mix_LoadWAV("audio/wallhit.wav");
    paddleHitSound = Mix_LoadWAV("audio/paddlehit.wav");
    buttonClickedSound = Mix_LoadWAV("audio/buttonclickedsound.mp3");

    music[0] = Mix_LoadMUS("audio/background music/duck.mp3");
    music[1] = Mix_LoadMUS("audio/background music/monkey.mp3");
    music[2] = Mix_LoadMUS("audio/background music/peeker.mp3");
    music[3] = Mix_LoadMUS("audio/background music/run.mp3");
    music[4] = Mix_LoadMUS("audio/background music/sneaky.mp3");
}

void playAudio(Mix_Chunk* s){
    Mix_PlayChannel(-1, s, 0);
}

void updateVolume(){
    Mix_VolumeMusic(Volume*2);
    Mix_Volume(-1, Volume);
}

void changeSong(){
    Mix_PlayMusic(music[SongSelected], -1);
}

#endif // _sound__H_