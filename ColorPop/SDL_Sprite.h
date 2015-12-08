#pragma once
#include "SDL.h"
#include"SDL_image.h"
class SDL_Sprite
{
public:
	SDL_Sprite();
	~SDL_Sprite();

public:
	void loadImage(SDL_Renderer*renderer, const char*file);										//����ͼƬ
	void textureRenderer(SDL_Renderer*renderer);														//����ͼƬ
	void textureRenderer(SDL_Renderer*renderer, SDL_Rect *clip);								//����ͼƬ
	void textureRenderer(SDL_Renderer*renderer, SDL_Rect*clip, int x, int y);				//����ͼƬ
	void textureRenderer(SDL_Renderer*renderer, int x, int y);									//����ͼƬ
	void setSpritePosition(int x, int y);																		//����λ��
	void setSprite(int n, int w, int h);																		//���òü�����
	void setRect(int x, int y, int w, int h);																	//���þ���
	
	int getWidth();																									//����ͼƬ���
	int getHight();																									//����ͼƬ�߶�
	int getPosX();																										//����x����
	int getPosY();																										//����y����

protected:
	SDL_Texture*tex;
	SDL_Rect*clip;																									//�ü�����
	int w;																												//ͼƬ���
	int h;																													//ͼƬ�߶�
	int x;																													//ͼƬx������
	int y;																													//ͼƬy������
	int spriteW;																										//������
	int spriteH;																										//����߶�
};

