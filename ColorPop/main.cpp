#include"SDL.h"
#include"SDL_ttf.h"
#include"SDL_mixer.h"
#include"SDL_image.h"
#include"SDL_Sprite.h"
#include"SDL_Hero.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<time.h>
#include<cmath>
#include"SDL_Enemy.h"
#include"SDL_EffectSound.h"
#include"SDL_Background.h"
#include"SDL_Word.h"
#include"SDL_MyGame.h"

using namespace std;

/*typedef struct
{
	int x;
	int y;
	int time;
	bool ifbe;
	SDL_Enemy enemy;
	SDL_Sprite enemsmall;
	bool iflife;
}position;*/

int main(int argc, char* args[])
{
	SDL_MyGame game;
	game.initGame();
	game.loadResources();
	game.gameMainLoop();
	return 0;
}