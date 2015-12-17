#include "SDL_MyGame.h"


SDL_MyGame::SDL_MyGame()
{
}


SDL_MyGame::~SDL_MyGame()
{
}

const int SDL_MyGame::REFRESH_TIME = 500;
const int SDL_MyGame::FRAMES_PER_SECOND = 60;
const int SDL_MyGame::SCREEN_WIDTH = 480;
const int SDL_MyGame::SCREEN_HIGHT = 640;
const int SDL_MyGame::ENEMY_BASE_CONST = 3;
const int SDL_MyGame::ENEMY_BASE_SPEED = 6;
const int SDL_MyGame::BACKGROUND_FRASH = 100;

void SDL_MyGame::initGame()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();
	window = SDL_CreateWindow("ColorPop", 500, 100, SCREEN_WIDTH, SCREEN_HIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	timeStart = SDL_GetTicks();
	frame = 0;
	framestart = 0;
	score = 0;
	enemyTime = 0;
	enemyCount = 0;
	enemySpeed = ENEMY_BASE_SPEED;
	enemyBaseMaxCount = 0;
	enemyMaxCount = ENEMY_BASE_CONST;
	mouseX = 0;
	mouseY = 0;
	quite = false;
	begin = false;
	SDL_CaptureMouse(SDL_TRUE);
	for (int i = 0; i < 4; i++)
	{
		posX[i] = i * 105;
	}
	for (int i = 0; i < 2; i++)
	{
		posY[i] = (i+1) * -105;
	}
	background.setRect(0, 0, 480, 640);

}
void SDL_MyGame::loadResources()
{
	/*����������������*/
	bubbleSound.loadSound("269583__ifrosta__bubble.wav");

	/*���ؾ���ͼ*/
	hero.loadImage(renderer, "PopSprite.png");
	hero.setSprite(4, 100, 100);

	/*���ء�������ͼ��*/
	restart.loadImage(renderer, "Restart.png");

	/*����logo*/
	logo.loadImage(renderer, "Logo.png");

	/*����"��ʼ"ͼ��*/
	begin_1.loadImage(renderer, "Begin-1.png");
	begin_2.loadImage(renderer, "Begin-2.png");

	/*��������*/
	word.loadFont("consola.ttf", 50);
	word.renderText(renderer, "score:", 50);
}

bool SDL_MyGame::checkCollide()
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

void SDL_MyGame::gameMainLoop()
{
	string text = word.changeIntToString(score);
	text = "Score:  " + text;
	word.renderText(renderer, text, 50);
	while (!quite)
	{
		/*��ʼ����ѭ��*/
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
					
							begin_2.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_2.getWidth() / 2, SCREEN_HIGHT / 2 - begin_2.getHight() / 2);
							hero.setHeroLive();
							hero.randomHeroColor();
							SDL_RenderPresent(renderer);
							score = 0;
							begin = true;
							enemyTime = SDL_GetTicks();
						}
					}
				}
			}
			SDL_RenderClear(renderer);
			/*if (cbgStart == 0)
			{
				//cbg.colorChange(renderer);
				cbg.colorChangeBackground(renderer);
				cbgStart = SDL_GetTicks();
			}*/

			/*if (SDL_GetTicks() - cbgStart >= 200)
			{
				//cbg.colorChange(renderer);
				cbg.colorChangeBackground(renderer);
				cbgStart = SDL_GetTicks();
			}*/
		//	background.colorChangeBackground(renderer);
			begin_1.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_1.getWidth() / 2, SCREEN_HIGHT / 2 - begin_1.getHight() / 2);
			logo.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_1.getWidth() / 2 - 100, SCREEN_HIGHT / 2 - begin_1.getHight() / 2 - 100);
			SDL_RenderPresent(renderer);
			if (SDL_GetTicks() - timeStart >= BACKGROUND_FRASH)
			{
				background.colorChangeBackground(renderer);
				timeStart = SDL_GetTicks();
			}
			if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
			{
				SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
				framestart = SDL_GetTicks();
			}
		}

		/*��Ϸ��ѭ��*/
		framestart = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quite = true;

			hero.moveHerobyMouse(e);
		}
		if (quite)
			continue;

		/*����*/
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


		/*if (cbgStart == 0)
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
		}*/

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
		if (SDL_GetTicks() - timeStart >= BACKGROUND_FRASH)
		{
			background.colorChangeBackground(renderer);
			timeStart = SDL_GetTicks();
		}
		if (SDL_GetTicks() - enemyTime > REFRESH_TIME)
		{
			enemyCount++;
			SDL_Enemy enemy;
			int x = rand() % 4;
			int y = rand() % 2;
			enemy.loadImage(renderer, "PopSprite.png");
			enemy.setSprite(4, 100, 100);
			enemy.randomEnemyColor();
			enemy.setSpritePosition(posX[x], posY[y]);
			enemy.setEnemySpeed(enemySpeed);
			if (score > 1000)
			{
				enemy.setEnemySpeed(score / 1000 + ENEMY_BASE_SPEED);
			}
			enemy.setEnemyAi();
			enemy.setEnemyLive();
			enemy.textureRendererColor(renderer);
			vecEnemy.push_back(enemy);
			enemyTime = SDL_GetTicks();
		}
		/*����*/
		//TextureRenderer(renderer, textexture, 25, 0, 100, 50);
		word.setFontPosition(25, 0);
		word.setFontSize(100, 50);
		word.textureRenderer(renderer);

		for (auto &a : vecEnemy)
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

			for (auto &a : vecEnemy)
			{
				if (a.ifEnemyLive())
				{
					enemy = a;
					if (checkCollide())
					{
						bubbleSound.playSound();
						if (a.getEnemyColorFlag() == hero.getHeroColorFlag())
						{
							score += 100;
							string text = word.changeIntToString(score);
							text = "Score:  " + text;
							word.renderText(renderer,text, 50);
							//textexture = RenderText(font, renderer, "Score: ", score, 50);
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

		for (auto a = vecEnemy.begin(); a != vecEnemy.end();)
		{
			if (vecEnemy.empty())
				break;
			if (!a->ifEnemyLive())
			{
				vecEnemy.erase(a);
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
							/*if (cbgStart == 0)
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
							}*/
							hero.setHeroLive();
							hero.randomHeroColor();
							SDL_RenderPresent(renderer);
							score = 0;
							begin = true;
							vecEnemy.clear();
							enemyTime = SDL_GetTicks();
							enemyCount = 0;
							string text = word.changeIntToString(score);
							text = "Score:  " + text;
							word.renderText(renderer, text, 50);
							//textexture = RenderText(font, renderer, "Score: ", score, 50);
						}
					}
				}
			}

			SDL_RenderClear(renderer);
			//ScollBackground(renderer, &bg, &bg2);
			//ScollBackground(renderer, &cbg1, &cbg2);
			/*if (cbgStart == 0)
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
			}*/
			if (SDL_GetTicks() - timeStart >= BACKGROUND_FRASH)
			{
				background.colorChangeBackground(renderer);
				timeStart = SDL_GetTicks();
			}
			restart.textureRenderer(renderer, SCREEN_WIDTH / 2 - restart.getWidth() / 2 + 20, SCREEN_HIGHT / 2 - restart.getHight() / 2);
			word.setFontPosition(180, 190);
			word.setFontSize(150, 100);	
			string text=word.changeIntToString(score);
			text = "Score:  " + text;
			word.renderText(renderer, text, 50);
			word.textureRenderer(renderer);
			//textextureend = RenderText(font, renderer, "Your Score: ", score, 100);
			//TextureRenderer(renderer, textexture, 180, 190, 150, 100);
			SDL_RenderPresent(renderer);
			if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
			{
				SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
			}
		}
	}
}