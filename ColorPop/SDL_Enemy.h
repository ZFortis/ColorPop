#pragma once
#include "SDL_Sprite.h"
#include "SDL.h"
#include"SDL_Hero.h"
#include"SDL_image.h"
class SDL_Enemy :
	public SDL_Sprite
{
public:
	SDL_Enemy();
	~SDL_Enemy();

public:
	bool ifEnemyLive();																//判断敌人是否死亡
	void randomEnemyColor();														//随机设置敌人颜色
	void moveEnemyAi(SDL_Hero hero);										//智能移动敌人			
	void moveEnemy();																//移动敌人
	bool ifOverScene();																//是否超出屏幕
	void randomEnemyPosition();													//随即设置敌人位置
	void setEnemyLive();																//诞生敌人
	void setEnemyDead();																//杀死敌人			
	void textureRendererColor(SDL_Renderer*renderer);					//根据颜色绘制敌人
	void setEnemySpeed(int s);														//设置敌人速度
	void setEnemyAi();																	//设置敌人AI
	int getEnemyColorFlag();															//返回敌人颜色标志

private:
	static int seed;																		//随机颜色种子
	bool live;																				//敌人的生死
	int colorflag;																			//颜色标志
	int speed;																				//敌人移动速度
	int aiFlag;																			//AI标志
};

