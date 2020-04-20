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
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y+5;
	bottomA = a.y + a.h-5;

	//Calculate the sides of rect B
	leftB = b.x+5;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;


	if (bottomA > 540){
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

