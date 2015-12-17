#pragma once
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
using namespace std;

class SDL_MyGame
{
public:
	SDL_MyGame();
	~SDL_MyGame();
	void initGame();
	void loadResources();
	void gameMainLoop();

protected:
	bool checkCollide();

protected:
	static const int REFRESH_TIME;
	static const int FRAMES_PER_SECOND;
	static const int SCREEN_WIDTH;
	static const int SCREEN_HIGHT;
	static const int ENEMY_BASE_CONST;
	static const int ENEMY_BASE_SPEED;
	static const int BACKGROUND_FRASH;

	SDL_Window*window;
	SDL_Renderer*renderer;
	SDL_Word word;
	SDL_Sprite begin_1;
	SDL_Sprite begin_2;
	SDL_Sprite logo;
	SDL_Sprite restart;
	SDL_Hero hero;
	SDL_Enemy enemy;
	SDL_Event e;
	SDL_EffectSound bubbleSound;
	Uint32 timeStart;
	int frame;
	int framestart;
	int score;
	int enemyTime;
	int enemyCount;
	int enemyBaseSpeed;
	int enemySpeed;
	int enemyBaseMaxCount;
	int enemyMaxCount;
	int mouseX;
	int mouseY;
	bool quite;
	bool begin;
	int posX[4];
	int posY[2];
	vector<SDL_Enemy> vecEnemy;
	SDL_Background background;

};

