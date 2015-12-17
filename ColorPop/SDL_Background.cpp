#include "SDL_Background.h"


SDL_Background::SDL_Background()
{
	colorFlag = 0;
	vecFlag = 1;
	color.a = 1;
	color.r = 0;
	color.g = 0;
	color.b = 0;
}


SDL_Background::~SDL_Background()
{
}

void SDL_Background::colorChangeBackground(SDL_Renderer*renderer)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	//SDL_SetRenderDrawColor(renderer, backgroundColor[colorFlag].r, backgroundColor[colorFlag].g, backgroundColor[colorFlag].b, backgroundColor[colorFlag].a);
	colorChange();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &rect);

}

void SDL_Background::colorChange()
{
	int colorChange = 10;
	if (colorFlag == 0)
	{
		if (color.r <= 255 - colorChange)
		{
			color.r += 10;
		}
		else if (color.g <= 255 - colorChange)
		{
			color.g += 10;
		}
		else if (color.b <= 255 - colorChange)
		{
			color.b += 10;
		}
		else
			colorFlag = 1;
	}
	if (colorFlag == 1)
	{
		if (color.b >= 0 + 2 * colorChange)
		{ 
			color.b -= 10;
		}
		else if (color.g >= 0 + 2 * colorChange)
		{
			color.g -= 10;
		}
	/*	else if (color.r >= 0 + 2 * colorChange)
		{
			color.r -= 10;
		}*/
		else
			colorFlag = 0;
	}
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