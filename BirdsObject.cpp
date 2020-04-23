#include "stdafx.h"
#include "BirdsObject.h"
#include "GameBase.h"
#include "InitFunction.h"

BirdsObject::BirdsObject(){
	xPos = 0;
	yPos = 0;
	widthFrame = 0;
	heightFrame = 0;
	frame = 0;
	inputType.up = 0;
	xValue = 0;
	yValue = 0;
	degree = 0;
	isDied = false;
	stayed = false;
}

BirdsObject::~BirdsObject(){

}

SDL_Rect BirdsObject::GetRectFrame (){
	SDL_Rect rectBird;
	rectBird.x = rect.x;
	rectBird.y = rect.y;
	rectBird.w = widthFrame;
	rectBird.h = heightFrame;
	return rectBird;
}

// Load hinh anh chimney
bool BirdsObject::LoadImg (std::string path, SDL_Renderer* screen){
	bool loadChimney = GameBase::LoadImg (path,screen);
	if (loadChimney){
		xPos = rect.x;
		yPos = rect.y;
		widthFrame = rect.w/FRAME_BIRDS;
		heightFrame = rect.h;
	}
	return loadChimney;
}

//Lay hinh anh chuyen dong
void BirdsObject::set_clip (){
	if (widthFrame > 0 && heightFrame >0){
		for (int i=0;i<FRAME_BIRDS;i++){
			frameChimney[i].x = i*widthFrame;
			frameChimney[i].y = 0;
			frameChimney[i].w = widthFrame;
			frameChimney[i].h = heightFrame;
		}
	}
}

void BirdsObject::Show (SDL_Renderer* des){
	
	if (fly == true && isDied == false && inputType.up == 1){
		frame++;
	}
	if (frame >=FRAME_BIRDS) frame = 0;
	SDL_Rect* currentClip = &frameChimney[frame];
	SDL_Rect renderQuad = {rect.x, rect.y, widthFrame, heightFrame};
	SDL_RenderCopyEx (des, p_object,currentClip,&renderQuad,degree,NULL,SDL_FLIP_NONE);
}

void BirdsObject::HandleInputAction (SDL_Event events, SDL_Renderer* screen){
	if (events.type == SDL_KEYDOWN && isDied == false){
		switch (events.key.keysym.sym )
		{
		case SDLK_SPACE:
			{
				stayed = false;
				inputType.up = PRESSED;
				yValue = -POWER_FLY;
				fly = true;
				
			}
			break;
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP){
		switch (events.key.keysym.sym )
		{
		case SDLK_SPACE:
			{
				inputType.up = UNPRESSED;
				fly = false;

			}
			break;
		default:
			break;
		}
		
	}

	
}

void BirdsObject::Doplayer (){
	if (isDied == false && stayed == false){
		if (inputType.up == PRESSED)  {
			yPos += yValue;
			if (degree>-30) degree-=15;
		}
		if (degree>90) degree=0;
		degree+=2;
		
		yValue += GRAVITY;
		yPos += yValue;
		if (yPos + heightFrame >= SCREEN_HEIGHT ) {
			yValue = 0;
			yPos -= yValue;
		}
		if (yPos + heightFrame   < 0) {
			yValue = GRAVITY;
			yPos += yValue;
		}
	}
	else if (isDied)
	{
		if (yPos+heightFrame<540){
			yPos+=15;
		}
		degree +=20;
		if (degree>90)degree=90;
		yValue = 0;
	}
	SetRect (xPos,yPos);

	
}

void BirdsObject::isDying (bool Check, SDL_Rect chimney){
	setIsDied (true);
	if (Check){
		xPos--;
	}
	if (yPos > chimney.y + 400){
		yPos++;
	}
	if (yPos<chimney.y){
		yPos--;
	}

}

