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

void TextObject::setColor (Uint8 red,Uint8 green, Uint8 blue){
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
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
		posText[0].x = SCREEN_WIDTH/2-155;
		posText[0].y = SCREEN_HEIGHT/2-225;
		break;
	case 1: 
		posText[1].x = 0;
		posText[1].y = 0;
		break;
	case 2: 
		posText[2].x = 260;
		posText[2].y = 50;
		break;
	case 3: 
		posText[3].x = 490;
		posText[3].y = 180;
		break;
	case 4: 
		posText[4].x = 490;
		posText[4].y = 250;
		break;
	case 5: 
		posText[5].x = 380;
		posText[5].y = 230;
		break;
	case 6: 
		posText[6].x = 380;
		posText[6].y = 275;
		break;
	case 7: 
		posText[7].x = 380;
		posText[7].y = 320;
		break;
		
	default:
		break;
	}
}