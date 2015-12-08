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

//�жϵ����Ƿ�����
bool SDL_Enemy::ifEnemyLive()
{
	return live;
}

//������õ�����ɫ
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

//�ƶ�����
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

//�Ƿ񳬳���Ļ													
bool SDL_Enemy::ifOverScene()
{
	if (x > 480 || y>640)
	{
		live = false;
		return true;
	}
	return false;
}

//�漴���õ���λ��
void SDL_Enemy::randomEnemyPosition()
{
	;
}

//��������
void SDL_Enemy::setEnemyLive()
{
	live = true;
}

//ɱ������														
void SDL_Enemy::setEnemyDead()
{
	live = false;
}

//������ɫ���Ƶ���
void SDL_Enemy::textureRendererColor(SDL_Renderer*renderer)
{
	textureRenderer(renderer, clip + colorflag);
}

/*���õ����ٶ�*/
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