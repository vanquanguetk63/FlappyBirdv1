#include "stdafx.h"
#include "MenuGame.h"
#include "GameBase.h"

MenuGame::MenuGame(){
	effect = false;
}

MenuGame::~MenuGame(){

}

bool MenuGame::LoadImg (std::string path, SDL_Renderer* screen){
	bool loadMenu = GameBase::LoadImg (path,screen);
	if (loadMenu==false){
		return false;
	}
	return loadMenu;
}

void MenuGame::setClip (){
	gSprite[0].x = 0;
	gSprite[0].y = 0;
	gSprite[0].w = 435;
	gSprite[0].h = 260;

	gSprite[1].x = 0;
	gSprite[1].y = 270;
	gSprite[1].w = 410;
	gSprite[1].h = 235;

	gSprite[2].x = 0;
	gSprite[2].y = 520;
	gSprite[2].w = 160;
	gSprite[2].h = 100;

	gSprite[3].x = 168;
	gSprite[3].y = 520;
	gSprite[3].w = 162;
	gSprite[3].h = 100;

	gSprite[4].x = 0;
	gSprite[4].y = 635;
	gSprite[4].w = 160;
	gSprite[4].h = 100;

	gSprite[5].x = 168;
	gSprite[5].y = 635;
	gSprite[5].w = 162;
	gSprite[5].h = 100;

	gSprite[6].x = 425;
	gSprite[6].y = 0;
	gSprite[6].w = 320;
	gSprite[6].h = 370;
}

void MenuGame::render_Clip (SDL_Renderer* des,int numberMenu){
	width = gSprite[numberMenu].w;
	height = gSprite[numberMenu].h;

	setRectxy (numberMenu);
	SDL_Rect* currentClip = &gSprite[numberMenu];
	SDL_Rect renderQuad = {rect.x, rect.y, width, height};
	SDL_RenderCopy(des, p_object,currentClip,&renderQuad);
}

bool MenuGame::Motion (SDL_Event events, int numberMenu ){
	setRectxy (numberMenu);
	if (events.button.x >=  rect.x
		&& events.button.x <=  rect.x+  gSprite[numberMenu].w
		&& events.button.y >=  rect.y
		&& events.button.y <=  rect.y +  gSprite[numberMenu].h){
			return true;
	}
	else
	{
		return false;
	}
}
void MenuGame::setRectxy (const int& numberMenu){
	switch (numberMenu)
	{
	case MENUPOS:
		rect.x = 135;
		rect.y = 190;
		break;
	case SCOREBOARD:
		rect.x = 190;
		rect.y = 130;
		break;
	case RESTART :
	case ERESTART:
		rect.x = 210;
		rect.y = 385;
		break;
	case BESTSCORE:
	case EBESTSCORE:
		rect.x = 400;
		rect.y = 385;
		break;
	case BOARD:
		rect.x = 238;
		rect.y = 100;
		break;
	default:
		break;
	}
}