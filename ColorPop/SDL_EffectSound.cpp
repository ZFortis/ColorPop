#include "SDL_EffectSound.h"


SDL_EffectSound::SDL_EffectSound()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512);
}


SDL_EffectSound::~SDL_EffectSound()
{
	Mix_CloseAudio();
}

void SDL_EffectSound::loadSound(const char*file)
{
	sound = Mix_LoadWAV(file);
}

void SDL_EffectSound::playSound()
{
	Mix_PlayChannel(-1, sound, 0);
}