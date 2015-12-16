#pragma once
#include"SDL_ttf.h"
#include<string>
#include<sstream>

using namespace std;
class SDL_Word
{
public:
	SDL_Word();
	~SDL_Word();

public:
	void loadFont(string name, int size);
	void renderText(SDL_Renderer*renderer, string text, int size);
	void textureRenderer(SDL_Renderer*renderer);
	void setFontPosition(int x, int y);
	void setFontSize(int w, int h);
	int getPosX();
	int getPosY();
	int getWidth();
	int getHight();
	string changeIntToString(int num);

protected:
	TTF_Font *font;
	SDL_Texture*tex;
	int x;
	int y;
	int w;
	int h;
};

