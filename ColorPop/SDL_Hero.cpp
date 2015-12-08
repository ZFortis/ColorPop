#include "SDL_Hero.h"
#include<stdlib.h>
#include<time.h>

SDL_Hero::SDL_Hero()
{
}


SDL_Hero::~SDL_Hero()
{
}

/*�������Ӣ����ɫ*/
void SDL_Hero::randomHeroColor()
{
	int seed = (int)time(0);
	srand(seed);
	colorflag = rand() % 4;
}

/*ɱ��Ӣ��*/
void SDL_Hero::setHeroDead()
{
	live = false;
}

/*����Ӣ��*/
void SDL_Hero::setHeroLive()
{
	live = true;
}

/*�ж�Ӣ���Ƿ���*/
bool SDL_Hero::ifHeroLive()
{
	return live;
}


/*ͨ������ƶ��ƶ�Ӣ��*/
void SDL_Hero::moveHerobyMouse(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		x = e.motion.x - 50;
		y = e.motion.y - 50;
		if (x > 380)
			x = 380;
		if (x < 0)
			x = 0;
		if (y > 540)
			y = 540;
		if (y < 0)
			y = 0;
	}
}

/*����������ϴβ�һ������ɫ*/
void SDL_Hero::randomHeroColordiff()
{
	int seed = (int)time(0);
	int color = colorflag;
	srand(seed);
	colorflag = rand() % 4;
	if (colorflag == color)
	{
		colorflag++;
		if (colorflag == 4)
		{
			colorflag -= 2;
		}
	}
}

/*������ɫ����Ӣ��*/
void SDL_Hero::textureRendererColor(SDL_Renderer*renderer)
{
	textureRenderer(renderer, clip+colorflag);
}

int SDL_Hero::getHeroColorFlag()
{
	return colorflag;
}