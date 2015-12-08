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
	bool ifEnemyLive();																//�жϵ����Ƿ�����
	void randomEnemyColor();														//������õ�����ɫ
	void moveEnemyAi(SDL_Hero hero);										//�����ƶ�����			
	void moveEnemy();																//�ƶ�����
	bool ifOverScene();																//�Ƿ񳬳���Ļ
	void randomEnemyPosition();													//�漴���õ���λ��
	void setEnemyLive();																//��������
	void setEnemyDead();																//ɱ������			
	void textureRendererColor(SDL_Renderer*renderer);					//������ɫ���Ƶ���
	void setEnemySpeed(int s);														//���õ����ٶ�
	void setEnemyAi();																	//���õ���AI
	int getEnemyColorFlag();															//���ص�����ɫ��־

private:
	static int seed;																		//�����ɫ����
	bool live;																				//���˵�����
	int colorflag;																			//��ɫ��־
	int speed;																				//�����ƶ��ٶ�
	int aiFlag;																			//AI��־
};

