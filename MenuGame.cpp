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
	gSprite[MENUPOS].x = 0;
	gSprite[MENUPOS].y = 0;
	gSprite[MENUPOS].w = 435;
	gSprite[MENUPOS].h = 260;

	gSprite[SCOREBOARD].x = 0;
	gSprite[SCOREBOARD].y = 270;
	gSprite[SCOREBOARD].w = 410;
	gSprite[SCOREBOARD].h = 235;

	gSprite[RESTART].x = 0;
	gSprite[RESTART].y = 520;
	gSprite[RESTART].w = 160;
	gSprite[RESTART].h = 100;

	gSprite[BESTSCORE].x = 168;
	gSprite[BESTSCORE].y = 520;
	gSprite[BESTSCORE].w = 162;
	gSprite[BESTSCORE].h = 100;

	gSprite[ERESTART].x = 0;
	gSprite[ERESTART].y = 635;
	gSprite[ERESTART].w = 160;
	gSprite[ERESTART].h = 100;

	gSprite[EBESTSCORE].x = 168;
	gSprite[EBESTSCORE].y = 635;
	gSprite[EBESTSCORE].w = 162;
	gSprite[EBESTSCORE].h = 100;

	gSprite[BOARD].x = 425;
	gSprite[BOARD].y = 0;
	gSprite[BOARD].w = 320;
	gSprite[BOARD].h = 370;
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