#include "SDL.h"
#include "SDL_ttf.h"
#include"SDL_mixer.h"
#include"SDL_image.h"
#include"SDL_Sprite.h"
#include "SDL_Hero.h"
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<time.h>
#include<cmath>
#include"SDL_Enemy.h"
#include "SDL_EffectSound.h"
#include "SDL_background.h"

using namespace std;

/*typedef struct
{
	int x;
	int y;
	int time;
	bool ifbe;
	SDL_Enemy enemy;
	SDL_Sprite enemsmall;
	bool iflife;
}position;*/

typedef struct
{
	int x;
	int y;
	int time;
	bool ifbe;
	SDL_Enemy enemy;
}position;
const int REFRESH_TIME=500;
const int FRAMES_PER_SECOND = 60;
const int SCREEN_WIDTH = 480;
const int SCREEN_HIGHT = 640;
SDL_Texture*CreatTexture(SDL_Surface*suf, SDL_Renderer*ren);
void TextureRenderer(SDL_Renderer*renderer, SDL_Texture*tex, int x, int y, int w, int h);
bool CheckCollide(SDL_Enemy &enemy, SDL_Hero hero);
//bool CheckCollideEnemy(SDL_Enemy &enemy1, SDL_Enemy enemy2);
//void TextureRenderer(SDL_Texture*tex, SDL_Renderer*renderer, int x, int y);
//void TextureRenderer(SDL_Texture*tex, SDL_Renderer*renderer, int x, int y, int w, int h);
void ScollBackground(SDL_Renderer*renderer, SDL_Sprite *bg1, SDL_Sprite *bg2);
void ScollBackground(SDL_Renderer*renderer, SDL_Background*bg1, SDL_Background*bg2);
SDL_Texture* RenderText(TTF_Font *font, SDL_Renderer*renderer, string text, int size);
SDL_Texture* RenderText(TTF_Font *font, SDL_Renderer*renderer, string text, int score, int size);
int rondom();

int main(int argc, char* args[])
{
	//启动SDL
	int posflag[4];
	int n = 0;
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() != 0)
	{
		return 0;
	}
	int frame = 0;
	int framestart = 0;
	SDL_Window*window = SDL_CreateWindow("ColorPop", 500, 100, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/*
	SDL_Texture*tbg=IMG_LoadTexture(renderer, "bg_03.jpg");
	SDL_Texture*tpop = IMG_LoadTexture(renderer, "pop-blue.png");
	if (tbg == nullptr||tpop==nullptr)
	{
	std::cout << "TEX" << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit;
	return 1;
	}
	//SDL_Texture*tex= CreatTexture(bmp, renderer);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tbg, NULL,NULL);
	SDL_QueryTexture(tpop, NULL, NULL, &w, &h);
	TextureRenderer(tpop, renderer, SCREEN_WIDTH / 2-w/2, SCREEN_HIGHT / 2-h/2);
	*/

	string name;
	int score = 0;
	name = "consola.ttf";
	TTF_Font *font = TTF_OpenFont(name.c_str(), 50);
	int killI;
	int countsb = 0;
	SDL_Texture*textexture = RenderText(font, renderer, "Score: ", score, 50);
	SDL_Texture*textextureend = RenderText(font, renderer, "Score: ", score, 100);
	SDL_Sprite bg, bg2, pop, begin_1, begin_2, logo, restart;
	SDL_Sprite herosmall, boom;
	SDL_Hero hero;
	SDL_Event e;
	SDL_Background cbg,cbg1,cbg2;
	SDL_EffectSound bubbleSound;
	Uint32 start = 0;
	int cbgStart = 0;
	/*position pos[8];
	for (int i = 50, j = 0; j<8; i += 55, j++)
	{
		pos[j].x = i;
		pos[j].y = -305;
		pos[j].time = 0;
		pos[j].ifbe = false;

		/*加载破裂图片
		boom.loadImage(renderer, "PopSpriteBoom.png");
		boom.setSprite(4,100, 100);

		/*加载敌人
		pos[j].enemy.loadImage(renderer, "PopSprite.png");
		pos[j].enemy.setSprite(4, 100, 100);

		pos[j].iflife = false;
	}*/
	int posX[4] = { 0, 105, 210, 315 };
	int posY[2] = { -100, -205 };
	vector<SDL_Enemy> pos;
	int enemyTime;
	int enemyCount = 0;
	int enemyBaseSpeed = 6;
	int enemySpeed = enemyBaseSpeed;
	int enemyBaseMaxCount = 3;
	int enemyMaxCount = enemyBaseMaxCount;
	int mouseX = 0, mouseY = 0;
	bool quite = false;
	bool begin = false;
	SDL_CaptureMouse(SDL_TRUE);
	/*加载泡泡破裂声音*/
	bubbleSound.loadSound("269583__ifrosta__bubble.wav");

	/*加载精灵图*/
	hero.loadImage(renderer, "PopSprite.png");
	hero.setSprite(4, 100, 100);

	
	/*加载背景图片*/
	bg.loadImage(renderer, "bg_05.jpg");
	bg2.loadImage(renderer, "bg_05.jpg");

	cbg1.loadImage(renderer, "background.png");
	cbg2.loadImage(renderer, "background2.png");

	/*加载“结束”图标*/
	restart.loadImage(renderer, "Restart.png");

	/*加载泡泡图片*/
	pop.loadImage(renderer, "pop-blue.png");

	/*加载logo*/
	logo.loadImage(renderer, "Logo.png");

	/*加载"开始"图标*/
	begin_1.loadImage(renderer, "Begin-1.png");
	begin_2.loadImage(renderer, "Begin-2.png");

	/*设置泡泡位置*/
	pop.setSpritePosition(SCREEN_WIDTH / 2 - pop.getWidth() / 2, SCREEN_HIGHT / 2 - pop.getHight() / 2);

	/*设置背景位置*/
	bg.setSpritePosition(0, 0);
	bg2.setSpritePosition(0, -1280);

	cbg1.setSpritePosition(0, 0);
	cbg2.setSpritePosition(0, -1280);

	//cbg.setRect(0, 0, SCREEN_WIDTH, SCREEN_HIGHT);

	/*主消息循环*/
	while (!quite)
	{
		/*开始界面循环*/
		while (!begin&&!quite)
		{
			framestart = SDL_GetTicks();
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quite = true;
				if (e.type = SDL_MOUSEBUTTONDOWN)
				{
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&mouseX, &mouseY);
						double l = sqrt(pow((240 - mouseX), 2) + pow((320 - mouseY), 2));
						if (l <= 50)
						{
							int heroX = 0;
							int heroY = 0;
							SDL_GetMouseState(&heroX, &heroY);
							hero.setSpritePosition(heroX - 50, heroY - 50);
							SDL_RenderClear(renderer);
							//ScollBackground(renderer, &bg, &bg2);
							ScollBackground(renderer, &cbg1, &cbg2);
							begin_2.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_2.getWidth() / 2, SCREEN_HIGHT / 2 - begin_2.getHight() / 2);
							hero.setHeroLive();
							hero.randomHeroColor();
							SDL_RenderPresent(renderer);
							start = SDL_GetTicks();
							score = 0;
							begin = true;
							enemyTime = SDL_GetTicks();
						}
					}
				}
			}
			countsb++;
			SDL_RenderClear(renderer);
			//ScollBackground(renderer, &bg, &bg2);
			//ScollBackground(renderer, &cbg1, &cbg2);
			if (cbgStart == 0)
			{
				//cbg.colorChange(renderer);
				cbg.colorChangeBackground(renderer);
				cbgStart = SDL_GetTicks();
			}

			if (SDL_GetTicks() - cbgStart >= 200)
			{
				//cbg.colorChange(renderer);
				cbg.colorChangeBackground(renderer);
				cbgStart = SDL_GetTicks();
			}
			begin_1.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_1.getWidth() / 2, SCREEN_HIGHT / 2 - begin_1.getHight() / 2);
			logo.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_1.getWidth() / 2 - 100, SCREEN_HIGHT / 2 - begin_1.getHight() / 2 - 100);
			SDL_RenderPresent(renderer);
			cout << "sdsd" << countsb << endl;
			if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
			{
				cout << "正常：" << SDL_GetTicks() - framestart << " " << SDL_GetTicks() << endl;
				SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
			}
			else
			{
				cout << "不正常：" << SDL_GetTicks() - framestart << endl;
			}
		}

		/*游戏内循环*/
		framestart = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quite = true;

			hero.moveHerobyMouse(e);
		}
		if (quite)
			continue;

		/*绘制*/
		SDL_RenderClear(renderer);
		/*for (int i = 0; i < 3; i++)
		{
		posflag[i] = rondom();
		if (!pos[posflag[i]].iflife)
		{
		if (posflag[i] > 0 && posflag[i] < 3)
		{
		if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i] + 1].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] + 3].ifbe&&!pos[posflag[i] + 4].ifbe&&!pos[posflag[i] + 5].ifbe)
		{
		pos[posflag[i]].ifbe = true;
		}
		}
		else
		{
		if (posflag[i] == 0)
		{
		if (!pos[posflag[i] + 1].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] + 4].ifbe&&!pos[posflag[i] + 5].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		if (posflag[i] == 3)
		{
		if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] + 3].ifbe&&!pos[posflag[i] + 4].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		}
		if (posflag[i] > 4 && posflag[i] < 7)
		{
		if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i] + 1].ifbe&&!pos[posflag[i]].ifbe&& !pos[posflag[i] - 3].ifbe&&!pos[posflag[i] - 4].ifbe&&!pos[posflag[i] - 5].ifbe)
		{
		if (!pos[posflag[i] + 3].ifbe&&!pos[posflag[i] + 4].ifbe&&!pos[posflag[i] + 5].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		}
		else
		{
		if (posflag[i] == 4)
		{
		if (!pos[posflag[i] + 1].ifbe&&!pos[posflag[i]].ifbe&& !pos[posflag[i] - 4].ifbe&&!pos[posflag[i] - 3].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] + 4].ifbe&&!pos[posflag[i] + 5].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		if (posflag[i] == 7)
		{
		if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i]].ifbe&& !pos[posflag[i] - 5].ifbe && !pos[posflag[i] - 4].ifbe&&!pos[posflag[i] + 3].ifbe&&!pos[posflag[i] + 4].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		}
		if (posflag[i] > 8 && posflag[i] < 11)
		{
		if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i] + 1].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] - 3].ifbe&&!pos[posflag[i] - 4].ifbe&&!pos[posflag[i] - 5].ifbe)
		{
		pos[posflag[i]].ifbe = true;
		}
		}
		else
		{
		if (posflag[i] == 8)
		{
		if (!pos[posflag[i] + 1].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] - 4].ifbe&&!pos[posflag[i] -3].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		if (posflag[i] == 11)
		{
		if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i]].ifbe&&!pos[posflag[i] - 5].ifbe&&!pos[posflag[i] - 4].ifbe)
		pos[posflag[i]].ifbe = true;
		}
		}
		}
		}*/

		//ScollBackground(renderer, &bg, &bg2);
		//ScollBackground(renderer, &cbg1, &cbg2);
		if (cbgStart == 0)
		{
			//cbg.colorChange(renderer);
			cbg.colorChangeBackground(renderer);
			cbgStart = SDL_GetTicks();
		}
		
		if (SDL_GetTicks() - cbgStart >= 200)
		{
			//cbg.colorChange(renderer);
			cbg.colorChangeBackground(renderer);
			cbgStart = SDL_GetTicks();
		}
		
		/*for (int i = 0; i < 3; i++)
		{
			posflag[i] = rondom();
			cout << posflag[i] << endl;
			if (!pos[posflag[i]].iflife&&!pos[posflag[i]].ifbe)
			{
				if (posflag[i] == 0)
				{
					if (!pos[posflag[i] + 1].ifbe&&!pos[posflag[i] + 2].ifbe)
					{
						pos[posflag[i]].ifbe = true;
						pos[posflag[i]].time = SDL_GetTicks();
					}
				}
				else if (posflag[i] == 1)
				{
					if (!pos[posflag[i] - 1].ifbe&&!pos[posflag[i] + 1].ifbe&&!pos[posflag[i] + 2].ifbe)
					{
						pos[posflag[i]].ifbe = true;
						pos[posflag[i]].time = SDL_GetTicks();
					}
				}
				else if (posflag[i]>1 && posflag[i] < 6)
				{
					if (!pos[posflag[i] - 2].ifbe&&!pos[posflag[i] - 1].ifbe&&!pos[posflag[i] + 1].ifbe&&!pos[posflag[i] + 2].ifbe)
					{
						pos[posflag[i]].ifbe = true;
						pos[posflag[i]].time = SDL_GetTicks();
					}
				}
				else if (posflag[i] == 6)
				{
					if (!pos[posflag[i] - 2].ifbe&&!pos[posflag[i] - 1].ifbe&&!pos[posflag[i] + 1].ifbe)
					{
						pos[posflag[i]].ifbe = true;
						pos[posflag[i]].time = SDL_GetTicks();
					}
				}
				else if (posflag[i] == 7)
				{
					if (!pos[posflag[i] - 2].ifbe&&!pos[posflag[i] - 1].ifbe)
					{
						pos[posflag[i]].ifbe = true;
						pos[posflag[i]].time = SDL_GetTicks();
					}
				}
			}
		}*/

	/*	if (pos[n].ifbe&&!pos[n].iflife)
		{
			cout << "................................................." << endl;
			pos[n].iflife = true;
			pos[n].enemy.randomEnemyColor();
			pos[n].enemy.setSpritePosition(pos[n].x - 55, pos[n].y);
			pos[n].enemy.setEnemySpeed(6);
			if (score > 1000)
			{
				pos[n].enemy.setEnemySpeed(score / 1000 + 6);
			}
			pos[n].enemy.setEnemyAi();
			pos[n].enemy.setEnemyLive();
			if (SDL_GetTicks() - pos[n].time >= 1000)
			{
				pos[n].ifbe = false;
			}
			//pos[n].enemy.textureRenderer(renderer, clip2, pos[n].x, pos[n].y);
			pos[n].enemy.textureRendererColor(renderer);
		}
		n++;
		if (n > 7)
			n = 0;*/
		if (SDL_GetTicks() - enemyTime > REFRESH_TIME)
		{

			enemyCount++;
			SDL_Enemy enemy;
			int x = rand() % 4;
			int y = rand() % 2;
			enemy.loadImage(renderer, "PopSprite.png");
			enemy.setSprite(4, 100, 100);
			enemy.randomEnemyColor();
			enemy.setSpritePosition(posX[x] , posY[y]);
			enemy.setEnemySpeed(enemySpeed);
			if (score > 1000)
			{
				enemy.setEnemySpeed(score / 1000 + enemyBaseSpeed);
			}
			enemy.setEnemyAi();
			enemy.setEnemyLive();
			enemy.textureRendererColor(renderer);
			pos.push_back(enemy);
			enemyTime = SDL_GetTicks();
		}
		/*文字*/
		TextureRenderer(renderer, textexture, 25, 0, 100, 50);

		for (auto &a : pos)
		{
			a.moveEnemy();
			//a.enemy.MoveEnemyAi();
			a.textureRendererColor(renderer);
			if (a.ifOverScene())
			{
				a.setEnemyDead();
				enemyCount--;
			}
		}
	

		/*for (auto &a : pos)
		{
			if (a.iflife&&a.enemy.ifEnemyLive())
			{
				a.enemy.moveEnemy();
				//a.enemy.MoveEnemyAi();
				a.enemy.textureRendererColor(renderer);
				if (a.enemy.ifOverScene())
				{
					a.ifbe = false;
					a.iflife = false;
					a.enemy.setEnemyDead();
				}
			}
		}*/

		if (hero.ifHeroLive())
		{
			hero.textureRendererColor(renderer);

			for (auto &a : pos)
			{
				if (a.ifEnemyLive())
				{
					if (CheckCollide(a, hero))
					{
						bubbleSound.playSound();
						if (a.getEnemyColorFlag() == hero.getHeroColorFlag())
						{
							score += 100;
							textexture = RenderText(font, renderer, "Score: ", score, 50);
							hero.randomHeroColordiff();
							enemyCount--;
							a.setEnemyDead();
							//boom.TextureRenderer(renderer, a.enemy.x, a.enemy.y);
						}
						else
						{
							hero.randomHeroColordiff();
							hero.setHeroDead();
							//quite = true;
						}
					}
				}
			}
		}

		for (auto a = pos.begin(); a != pos.end();)
		{
			if (pos.empty())
				break;
			if (!a->ifEnemyLive())
			{
				pos.erase(a);
			}
			else
			{
				a++;
			}
		}

		//pop.TextureRenderer(renderer, pop.x-50, pop.y-50);
		SDL_RenderPresent(renderer);
		if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
		}
		if (SDL_GetTicks() - framestart > 1000 / FRAMES_PER_SECOND)
		{
			cout << ".................<>...................." << endl;
		}

		
		while (!hero.ifHeroLive() && begin&&!quite)
		{

			framestart = SDL_GetTicks();
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quite = true;
				if (e.type = SDL_MOUSEBUTTONDOWN)
				{
					if (e.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&mouseX, &mouseY);
						double l = sqrt(pow((SCREEN_WIDTH / 2 - mouseX), 2) + pow((SCREEN_HIGHT / 2 - mouseY), 2));
						if (l <= 50)
						{
							int heroX = 0;
							int heroY = 0;
							SDL_GetMouseState(&heroX, &heroY);
							hero.setSpritePosition(heroX - 50, heroY - 50);
							SDL_RenderClear(renderer);
							//ScollBackground(renderer, &bg, &bg2);
							//ScollBackground(renderer, &cbg1, &cbg2);
							if (cbgStart == 0)
							{
								//cbg.colorChange(renderer);
								cbg.colorChangeBackground(renderer);
								cbgStart = SDL_GetTicks();
							}

							if (SDL_GetTicks() - cbgStart >= 200)
							{
								//cbg.colorChange(renderer);
								cbg.colorChangeBackground(renderer);
								cbgStart = SDL_GetTicks();
							}
							hero.setHeroLive();
							hero.randomHeroColor();
							SDL_RenderPresent(renderer);
							start = SDL_GetTicks();
							score = 0;
							begin = true;
							pos.clear();
							enemyTime = SDL_GetTicks();
							enemyCount = 0;
							textexture = RenderText(font, renderer, "Score: ", score, 50);
						}
					}
				}
			}

			SDL_RenderClear(renderer);
			cout << "<<<<<<<<<<<<<<<<<" << endl;
			//ScollBackground(renderer, &bg, &bg2);
			//ScollBackground(renderer, &cbg1, &cbg2);
			if (cbgStart == 0)
			{
				//cbg.colorChange(renderer);
				cbg.colorChangeBackground(renderer);
				cbgStart = SDL_GetTicks();
			}

			if (SDL_GetTicks() - cbgStart >= 200)
			{
				//cbg.colorChange(renderer);
				cbg.colorChangeBackground(renderer);
				cbgStart = SDL_GetTicks();
			}
			restart.textureRenderer(renderer, SCREEN_WIDTH / 2 - restart.getWidth() / 2 + 20, SCREEN_HIGHT / 2 - restart.getHight() / 2);
			textextureend = RenderText(font, renderer, "Your Score: ", score, 100);
			TextureRenderer(renderer, textexture, 180, 190, 150, 100);
			SDL_RenderPresent(renderer);
			if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
			{
				cout << SDL_GetTicks() - framestart << endl;
				SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
			}
			else
			{
				cout << "<><>" << SDL_GetTicks() - framestart << endl;
			}
		}
	}

	//	SDL_Delay(5000);
	SDL_DestroyRenderer(renderer);
	//SDL_DestroyTexture(tbg);
	SDL_DestroyWindow(window);
	//退出SDL 
	SDL_Quit();

	return 0;
}

void ScollBackground(SDL_Renderer*renderer, SDL_Sprite*bg1, SDL_Sprite*bg2)
{
	bg1->setSpritePosition(bg1->getPosX(), bg1->getPosY() + 5);
	bg2->setSpritePosition(bg2->getPosX(), bg2->getPosY() + 5);
	bg1->textureRenderer(renderer);
	bg2->textureRenderer(renderer);
	if (bg1->getPosY() >= 1280)
		bg1->setSpritePosition(bg1->getPosX(),-1280);
	if (bg2->getPosY() >= 1280)
		bg2->setSpritePosition(bg1->getPosX(), -1280);
}

void ScollBackground(SDL_Renderer*renderer, SDL_Background*bg1, SDL_Background*bg2)
{
	bg1->setSpritePosition(bg1->getPosX(), bg1->getPosY() + 5);
	bg2->setSpritePosition(bg2->getPosX(), bg2->getPosY() + 5);
	bg1->textureRenderer(renderer);
	bg2->textureRenderer(renderer);
	if (bg1->getPosY() >= 1280)
		bg1->setSpritePosition(bg1->getPosX(), -1280);
	if (bg2->getPosY() >= 1280)
		bg2->setSpritePosition(bg1->getPosX(), -1280);
}

bool CheckCollide(SDL_Enemy &enemy, SDL_Hero hero)
{
	double CenterEnemyX, CenterEnemyY;
	double CenterHeroX, CenterHeroY;
	CenterEnemyX = enemy.getPosX();

	CenterEnemyY = enemy.getPosY();

	CenterHeroX = hero.getPosX();
	CenterHeroY = hero.getPosY();
	if (sqrt(pow((CenterEnemyX - CenterHeroX), 2) + pow((CenterEnemyY - CenterHeroY), 2)) <= 100)
	{
		enemy.setEnemyDead();
		return true;
	}
	return false;
}
/*
bool CheckCollideEnemy(SDL_Enemy &enemy1, SDL_Enemy enemy2)
{
	double CenterEnemy1X, CenterEnemy1Y;
	double CenterEnemy2X, CenterEnemy2Y;
	CenterEnemy1X = enemy1.x + 50;
	CenterEnemy1Y = enemy1.y + 50;
	CenterEnemy2X = enemy2.x;
	CenterEnemy2Y = enemy2.y;
	if (sqrt(pow((CenterEnemy1X - CenterEnemy2X), 2) + pow((CenterEnemy1Y - CenterEnemy2Y), 2)) <= 150)
	{
		return true;
	}
	return false;
}*/

int rondom()
{
	static int seed = (int)time(0);
	int addseed = 100;
	srand(seed);
	seed += addseed;
	return rand() % 8;
}

void TextureRenderer(SDL_Renderer*renderer, SDL_Texture*tex, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

SDL_Texture* RenderText(TTF_Font*font, SDL_Renderer*renderer, string text, int size)
{

	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}

SDL_Texture* RenderText(TTF_Font*font, SDL_Renderer*renderer, string text, int score, int size)
{
	SDL_Color color = { 255, 255, 255, 255 };
	string s;
	stringstream ss;
	ss << score;
	ss >> s;
	s = " " + s;
	text = text + s;

	SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	//TTF_CloseFont(font);
	return texture;
}

