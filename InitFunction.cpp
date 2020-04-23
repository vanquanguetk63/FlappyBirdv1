#include "stdafx.h"
#include "InitFunction.h"
#include "ImpTimer.h"

bool SDLInitfunction::CheckCollision (const SDL_Rect& a,const  SDL_Rect& b){
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x - 7;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w-5;
	topB = b.y;
	bottomB = b.y + b.h-7;


	if (bottomA >= SCREEN_HEIGHT-100){
		return true;
	}
	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

