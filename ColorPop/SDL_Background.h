
#include "SDL_Sprite.h"
class SDL_Background :
	public SDL_Sprite
{
public:
	SDL_Background();
	~SDL_Background();

public:
	void colorChangeBackground(SDL_Renderer*renderer);
	void colorChange(SDL_Renderer*renderer);
	void scollBackground(SDL_Renderer*renderer, SDL_Background bg1, SDL_Background bg2);

protected:
	SDL_Color backgroundColor[9];
	int colorFlag;
	int vecFlag;
};
