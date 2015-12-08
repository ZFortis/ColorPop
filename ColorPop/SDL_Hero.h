#pragma once
#include "SDL_Sprite.h"
class SDL_Hero :
	public SDL_Sprite
{
public:
	SDL_Hero();
	~SDL_Hero();

public:
	void randomHeroColor();														//�������Ӣ����ɫ
	void setHeroDead();																//ɱ��Ӣ��
	void setHeroLive();																//����Ӣ��
	bool ifHeroLive();																	//�ж�Ӣ���Ƿ���							
	void moveHerobyMouse(SDL_Event e);										//ͨ������ƶ��ƶ�Ӣ��
	void randomHeroColordiff();													//����������ϴβ�һ������ɫ
	void textureRendererColor(SDL_Renderer*renderer);					//������ɫ����Ӣ��
	int getHeroColorFlag();															//������ɫ��־

private:
	bool live;																				//Ӣ�۵�����
	int colorflag;																			//��ɫ��־
};

