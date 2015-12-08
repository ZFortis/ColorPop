#pragma once
#include "SDL.h"
#include"SDL_image.h"
class SDL_Sprite
{
public:
	SDL_Sprite();
	~SDL_Sprite();

public:
	void loadImage(SDL_Renderer*renderer, const char*file);										//加载图片
	void textureRenderer(SDL_Renderer*renderer);														//绘制图片
	void textureRenderer(SDL_Renderer*renderer, SDL_Rect *clip);								//绘制图片
	void textureRenderer(SDL_Renderer*renderer, SDL_Rect*clip, int x, int y);				//绘制图片
	void textureRenderer(SDL_Renderer*renderer, int x, int y);									//绘制图片
	void setSpritePosition(int x, int y);																		//设置位置
	void setSprite(int n, int w, int h);																		//设置裁剪矩形
	void setRect(int x, int y, int w, int h);																	//设置矩形
	
	int getWidth();																									//返回图片宽度
	int getHight();																									//返回图片高度
	int getPosX();																										//返回x坐标
	int getPosY();																										//返回y坐标

protected:
	SDL_Texture*tex;
	SDL_Rect*clip;																									//裁剪矩形
	int w;																												//图片宽度
	int h;																													//图片高度
	int x;																													//图片x轴坐标
	int y;																													//图片y轴坐标
	int spriteW;																										//精灵宽度
	int spriteH;																										//精灵高度
};

