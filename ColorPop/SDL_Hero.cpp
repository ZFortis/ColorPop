#include "SDL_Hero.h"
#include<stdlib.h>
#include<time.h>

SDL_Hero::SDL_Hero()
{
}


SDL_Hero::~SDL_Hero()
{
}

/*随机设置英雄颜色*/
void SDL_Hero::randomHeroColor()
{
	int seed = (int)time(0);
	srand(seed);
	colorflag = rand() % 4;
}

/*杀死英雄*/
void SDL_Hero::setHeroDead()
{
	live = false;
}

/*复活英雄*/
void SDL_Hero::setHeroLive()
{
	live = true;
}

/*判断英雄是否存活*/
bool SDL_Hero::ifHeroLive()
{
	return live;
}


/*通过鼠标移动移动英雄*/
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

/*随机设置与上次不一样的颜色*/
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

/*根据颜色绘制英雄*/
void SDL_Hero::textureRendererColor(SDL_Renderer*renderer)
{
	textureRenderer(renderer, clip+colorflag);
}

int SDL_Hero::getHeroColorFlag()
{
	return colorflag;
}