#include "stdafx.h"
#include "TextObject.h"

TextObject::TextObject(){
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	texture = NULL;
}

TextObject::~TextObject(){

}

bool TextObject::LoadFromRenderText (TTF_Font* gFont, SDL_Renderer* screen){
	SDL_Color color = {0,0,0};
	textColor = color;
	SDL_Surface* textSurface = TTF_RenderText_Solid (gFont, strCont.c_str (), textColor);
	if (textSurface){
		texture = SDL_CreateTextureFromSurface(screen, textSurface);
		width = textSurface->w;
		height = textSurface->h;

		SDL_FreeSurface (textSurface);
	}
	return texture != NULL;
}

void TextObject::Free (){
	if (texture != NULL){
		SDL_DestroyTexture (texture);
		texture = NULL;
	}
}


void TextObject::Render (SDL_Renderer* screen, int numberText, SDL_Rect* clip /* = NULL */, double angle/* =0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */){
	setRectText (numberText);
	SDL_Rect renderQuad = {posText[numberText].x,posText[numberText].y,width,height};
	if (clip!=NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy (screen,texture,clip,&renderQuad);
}

void TextObject::setRectText(int numberText){
	
	switch (numberText)
	{
	case 0: 
		posText[MENU].x = X_MENU;
		posText[MENU].y = Y_MENU;
		break;
	case 1: 
		posText[SCORE].x = X_SCORE;
		posText[SCORE].y = Y_SCORE;
		break;
	case 2: 
		posText[OVER].x = X_OVER;
		posText[OVER].y = Y_OVER;
		break;
	case 3: 
		posText[SCOREFINAL].x = X_SCOREFINAL;
		posText[SCOREFINAL].y = Y_SCOREFINAL;
		break;
	case 4: 
		posText[BEST].x = X_BEST;
		posText[BEST].y = Y_BEST;
		break;
	case 5: 
		posText[BEST1].x = X_BEST1;
		posText[BEST1].y = Y_BEST1;
		break;
	case 6: 
		posText[BEST2].x = X_BEST2;
		posText[BEST2].y = Y_BEST2;
		break;
	case 7: 
		posText[BEST3].x = X_BEST3;
		posText[BEST3].y = Y_BEST3;
		break;
		
	default:
		break;
	}
}