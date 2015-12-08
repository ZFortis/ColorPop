#include "SDL_Enemy.h"
#include<stdlib.h>
#include<time.h>

SDL_Enemy::SDL_Enemy()
{
}


SDL_Enemy::~SDL_Enemy()
{
}

int SDL_Enemy::seed = (int)time(0);

//判断敌人是否死亡
bool SDL_Enemy::ifEnemyLive()
{
	return live;
}

//随机设置敌人颜色
void SDL_Enemy::randomEnemyColor()
{
	int addseed = (int)time(0);
	int add;
	srand(seed);
	colorflag = 0;
	colorflag = rand() % 4;
	srand(addseed);
	add = rand() % 25;
	seed += add;
}

//移动敌人
void SDL_Enemy::moveEnemyAi(SDL_Hero hero)
{
	;
}

void SDL_Enemy::moveEnemy()
{
	y += speed;
	if (aiFlag == 1)
	{
		x += 2;
	}
	if (aiFlag == 2)
	{
		x -= 2;
	}
}

//是否超出屏幕													
bool SDL_Enemy::ifOverScene()
{
	if (x > 480 || y>640)
	{
		live = false;
		return true;
	}
	return false;
}

//随即设置敌人位置
void SDL_Enemy::randomEnemyPosition()
{
	;
}

//诞生敌人
void SDL_Enemy::setEnemyLive()
{
	live = true;
}

//杀死敌人														
void SDL_Enemy::setEnemyDead()
{
	live = false;
}

//根据颜色绘制敌人
void SDL_Enemy::textureRendererColor(SDL_Renderer*renderer)
{
	textureRenderer(renderer, clip + colorflag);
}

/*设置敌人速度*/
void SDL_Enemy::setEnemySpeed(int s)
{
	speed = s;
}

int SDL_Enemy::getEnemyColorFlag()
{
	return colorflag;
}

void SDL_Enemy::setEnemyAi()
{
	int addseed = (int)time(0);
	int add;
	int flag;
	srand(seed);
	flag = rand() % 5;
	if (flag < 3&& x < 240)
	{
		aiFlag = 1;
	}
	else if (flag < 3 && x >= 240)
	{
		aiFlag = 2;
	}
	else
	{
		aiFlag = 0;
	}
	srand(addseed);
	add = rand() % 25;
	seed += add;
}