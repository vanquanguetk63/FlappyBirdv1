#ifndef GAME_BASE_H_
#define GAME_BASE_H_

#include "InitFunction.h"

class GameBase {
public:
	GameBase();
	~GameBase();

	void SetRect (const int& x, const int& y) {rect.x = x; rect.y = y;}
	SDL_Rect GetRect() const {return rect;}
	SDL_Texture* GetObject() const {return p_object;}
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();
	bool loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *gFont ,SDL_Renderer* screen);
	
	void render( int x, int y, SDL_Rect* clip = NULL, 
			double angle = 0.0, SDL_Point* center = NULL,
			SDL_RendererFlip flip = SDL_FLIP_NONE ); 

protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
};

#endif