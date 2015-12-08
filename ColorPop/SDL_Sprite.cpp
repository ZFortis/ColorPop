#include "SDL_Sprite.h"


SDL_Sprite::SDL_Sprite()
{
}


SDL_Sprite::~SDL_Sprite()
{
}

/*加载图片*/
void SDL_Sprite::loadImage(SDL_Renderer*renderer, const char*file)
{
	tex = IMG_LoadTexture(renderer, file);
	if (tex == nullptr)
	{
		SDL_Quit();
	}
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
}

/*绘制图片*/
void SDL_Sprite::textureRenderer(SDL_Renderer*renderer, SDL_Rect*clip, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, clip, &dst);
}

/*绘制图片*/
void SDL_Sprite::textureRenderer(SDL_Renderer*renderer)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

/*绘制图片*/
void SDL_Sprite::textureRenderer(SDL_Renderer*renderer, int x, int y)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

/*绘制图片*/
void SDL_Sprite::textureRenderer(SDL_Renderer*renderer, SDL_Rect *clip)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = spriteW;
	dst.h = spriteH;
	SDL_RenderCopy(renderer, tex, clip, &dst);
}

/*得到图片宽度*/
int SDL_Sprite::getWidth()
{
	return w;
}

/*得到图片高度*/
int SDL_Sprite::getHight()
{
	return h;
}

/*设置位置*/
void SDL_Sprite::setSpritePosition(int x, int y)
{
	this->x = x;
	this->y = y;
}


/*设置裁剪矩形*/
void SDL_Sprite::setSprite(int n,int w, int h)
{
	clip = new SDL_Rect[n];
	for (int i = 0; i < n; i++)
	{
		clip[i].x = i * w;
		clip[i].y = 0;
		clip[i].w = w;
		clip[i].h = h;
	}
	spriteW = w;
	spriteH = h;
}

int SDL_Sprite::getPosX()
{
	return x;
}

int SDL_Sprite::getPosY()
{
	return y;
}

void SDL_Sprite::setRect(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}