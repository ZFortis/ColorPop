#include "SDL_Background.h"


SDL_Background::SDL_Background()
{
	backgroundColor[0] = { 255, 102, 0, 1 };
	backgroundColor[1] = { 255, 187, 28, 1 };
	backgroundColor[2] = { 162, 183, 0, 1 };
	backgroundColor[3] = { 197, 218, 1, 1 };
	backgroundColor[4] = { 67, 161, 2, 1 };
	backgroundColor[5] = { 85, 162, 85, 1 };
	backgroundColor[6] = { 4, 159, 241, 1 };
	backgroundColor[7] = { 6, 95, 185, 1 };
	backgroundColor[8] = { 255, 255, 255, 1 };
	colorFlag = 0;
	vecFlag = 1;
}


SDL_Background::~SDL_Background()
{
}

void SDL_Background::colorChangeBackground(SDL_Renderer*renderer)
{
	if (vecFlag == 1)
	{
		colorFlag++;
	}
	if (vecFlag == 2)
	{
		colorFlag--;
	}

	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	//SDL_SetRenderDrawColor(renderer, backgroundColor[colorFlag].r, backgroundColor[colorFlag].g, backgroundColor[colorFlag].b, backgroundColor[colorFlag].a);
	SDL_SetRenderDrawColor(renderer, 194, 199, 203, 1);
	SDL_RenderFillRect(renderer, &rect);

	if (colorFlag == 0)
	{
		vecFlag = 1;
	}
	if (colorFlag == 7)
	{
		vecFlag = 2;
	}
}

void SDL_Background::colorChange(SDL_Renderer*renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, backgroundColor[8].r, backgroundColor[8].g, backgroundColor[8].b, backgroundColor[8].a);
	SDL_RenderFillRect(renderer, &rect);
	backgroundColor[8].r -= 10;
	backgroundColor[8].g -= 10;
	backgroundColor[8].b -= 10;
	if (backgroundColor[8].r <= 50)
	{
		backgroundColor[8].r = 255;
	}
/*	if (backgroundColor[8].g <= 50)
	{
		backgroundColor[8].g = 255;
	}
	if (backgroundColor[8].b <= 50)
	{
		backgroundColor[8].b = 255;
	}*/
}

void SDL_Background::scollBackground(SDL_Renderer*renderer, SDL_Background bg1, SDL_Background bg2)
{
	bg1.y += 5;
	bg2.y += 5;
	bg1.textureRenderer(renderer);
	bg2.textureRenderer(renderer);
	if (bg1.y >= 1280)
		bg1.y = -1280;
	if (bg2.y >= 1280)
		bg2.y = -1280;
}