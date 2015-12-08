#pragma once
#include "SDL_Sprite.h"
class SDL_Hero :
	public SDL_Sprite
{
public:
	SDL_Hero();
	~SDL_Hero();

public:
	void randomHeroColor();														//随机设置英雄颜色
	void setHeroDead();																//杀死英雄
	void setHeroLive();																//复活英雄
	bool ifHeroLive();																	//判断英雄是否存活							
	void moveHerobyMouse(SDL_Event e);										//通过鼠标移动移动英雄
	void randomHeroColordiff();													//随机设置与上次不一样的颜色
	void textureRendererColor(SDL_Renderer*renderer);					//根据颜色绘制英雄
	int getHeroColorFlag();															//返回颜色标志

private:
	bool live;																				//英雄的生死
	int colorflag;																			//颜色标志
};

