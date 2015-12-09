#pragma once
#include<string>
#include"SDL_mixer.h"
using namespace::std;

class SDL_EffectSound
{
public:
	SDL_EffectSound();
	~SDL_EffectSound();

public:
	void loadSound(const char *file);
	void playSound();

protected:
	Mix_Chunk *sound;
};

