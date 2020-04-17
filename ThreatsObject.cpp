#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject(){
	xPos = 0;
	yPos = 0;
}

ThreatsObject::~ThreatsObject(){

}

SDL_Rect ThreatsObject::GetRectFrame (){
	SDL_Rect rectObject;
	rectObject.x = rect.x;
	rectObject.y = rect.y;
	rectObject.w = widthFrame;
	rectObject.h = heightFrame;
	return rectObject;
}

bool ThreatsObject::LoadImgground (std::string path, SDL_Renderer* screen){
	bool loadImg = GameBase::LoadImg (path,screen);
	if (loadImg){
		xPos = rect.x;
		rect.y = POSY_GROUND;
		yPos = rect.y;
	}
	return loadImg;
}

void ThreatsObject::UpdateGround (){
	xPos--;
	if (xPos + POSX_LIMITED_GROUND ==0){
		xPos = POSX_LIMITED_GROUND;
	}
	SetRect (xPos,yPos);
}

void ThreatsObject::setPosxy (const int& xPos_, const int& yPos_){
	xPos = xPos_;
	yPos = yPos_;
}



bool ThreatsObject::LoadImgchimney (std::string path, SDL_Renderer* screen){
	bool loadImg = GameBase::LoadImg (path,screen);
	if (loadImg){
		widthFrame = rect.w;
		heightFrame = rect.h;
		return loadImg;
	}
	else return false;
}

void ThreatsObject::UpdateChimney (){
	xPos--;
	if (xPos + widthFrame <0){
		xPos = POSX_CHIMNEY_RETURNED;
	}
	SetRect (xPos,yPos);
}