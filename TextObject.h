#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "InitFunction.h"

class TextObject
{
public:
	TextObject();
	~TextObject();

	bool loadMedia(std::string path);
	bool LoadFromRenderText(TTF_Font* gFont, SDL_Renderer* screen);
	void Free();
	void setColor(Uint8 red,Uint8 green, Uint8 blue);

	void Render(SDL_Renderer* screen, 
				int numberText, SDL_Rect* clip = NULL,
				double angle=0.0, SDL_Point* center = NULL,
				SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	int GetWidth() const {return width;}
	int GetHeight() const {return height;}
	void SetText(const std::string& text) {strCont = text;}
	std::string getText() const {return strCont;}

	void setRectText(int numberText);

private:
	std::string strCont;
	SDL_Color textColor;
	SDL_Texture*  texture;
	int width;
	int height;
	SDL_Rect posText[totalText];	
};

#endif
