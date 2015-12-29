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
	/*加载泡泡破裂声音*/
	bubbleSound.loadSound("269583__ifrosta__bubble.wav");

	/*加载精灵图*/
	hero.loadImage(renderer, "bubbleSprite.png");
	hero.setSprite(4, 100, 100);

	/*加载“结束”图标*/
	restart.loadImage(renderer, "Restart.png");

	/*加载logo*/
	logo.loadImage(renderer, "Logo.png");

	/*加载"开始"图标*/
	begin_1.loadImage(renderer, "Begin-1.png");
	begin_2.loadImage(renderer, "Begin-2.png");

	/*加载文字*/
	word.loadFont("consola.ttf", 50);
	word.renderText(renderer, "score:", 50);

	bg1.loadImage(renderer, "black_3.png");
	bg2.loadImage(renderer, "black_4.png");
	bg1.setRect(0, 0, 480, 640);
	bg2.setRect(0, -640, 480, 640);
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

void SDL_MyGame::scollBackground(int speed)
{
	bg1.setSpritePosition(bg1.getPosX(), bg1.getPosY() + speed - 1);
	bg2.setSpritePosition(bg2.getPosX(), bg2.getPosY() + speed - 1);
	bg1.textureRenderer(renderer);
	bg2.textureRenderer(renderer);
	if (bg1.getPosY() >= 640)
		bg1.setRect(bg1.getPosX(), -640, bg1.getWidth(), bg1.getHight());
	if (bg2.getPosY() >= 640)
		bg2.setRect(bg2.getPosX(), -640, bg2.getWidth(), bg2.getHight());
}

void SDL_MyGame::gameMainLoop()
{
	SDL_CaptureMouse(SDL_TRUE);
	string text = word.changeIntToString(score);
	text = "Score:  " + text;
	word.renderText(renderer, text, 50);
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
			//background.scollBackground(renderer, bg1, bg2);
			scollBackground(enemySpeed);
			begin_1.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_1.getWidth() / 2, SCREEN_HIGHT / 2 - begin_1.getHight() / 2);
			logo.textureRenderer(renderer, SCREEN_WIDTH / 2 - begin_1.getWidth() / 2 - 100, SCREEN_HIGHT / 2 - begin_1.getHight() / 2 - 100);
			
			SDL_RenderPresent(renderer);
			/*if (SDL_GetTicks() - timeStart >= BACKGROUND_FRASH)
			{
				background.colorChangeBackground(renderer);
				timeStart = SDL_GetTicks();
			}*/
			//background.scollBackground(renderer, bg1, bg2);
			bg1.textureRenderer(renderer);
			bg2.textureRenderer(renderer);
			if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
			{
				SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
				framestart = SDL_GetTicks();
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

		scollBackground(enemySpeed);

		if (SDL_GetTicks() - enemyTime > REFRESH_TIME)
		{
			enemyCount++;
			SDL_Enemy enemy;
			int x = rand() % 4;
			int y = rand() % 2;
			enemy.loadImage(renderer, "bubbleSprite.png");
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
		/*文字*/
		//TextureRenderer(renderer, textexture, 25, 0, 100, 50);
		word.setFontPosition(25, 0);
		word.setFontSize(100, 50);
		word.textureRenderer(renderer);

		for (auto &a : vecEnemy)
		{
			a.moveEnemy();
			a.textureRendererColor(renderer);
			if (a.ifOverScene())
			{
				a.setEnemyDead();
				enemyCount--;
			}
		}
		
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
						}
					}
				}
			}

			SDL_RenderClear(renderer);
			
			scollBackground(enemySpeed);
			restart.textureRenderer(renderer, SCREEN_WIDTH / 2 - restart.getWidth() / 2 + 20, SCREEN_HIGHT / 2 - restart.getHight() / 2);
			word.setFontPosition(180, 190);
			word.setFontSize(150, 100);	
			string text=word.changeIntToString(score);
			text = "Score:  " + text;
			word.renderText(renderer, text, 50);
			word.textureRenderer(renderer);

			SDL_RenderPresent(renderer);
			if (SDL_GetTicks() - framestart < 1000 / FRAMES_PER_SECOND)
			{
				SDL_Delay((1000 / FRAMES_PER_SECOND) - (SDL_GetTicks() - framestart));
			}
		}
	}
}