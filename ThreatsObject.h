#ifndef GROUND_OBJECT_H_
#define GROUND_OBJECT_H_

#include "GameBase.h"

class ThreatsObject : public GameBase{
public:
	ThreatsObject();
	~ThreatsObject();

	bool LoadImgground(std::string path, SDL_Renderer* screen);
	bool LoadImgchimney(std::string path, SDL_Renderer* screen);
	void UpdateGround( );
	void UpdateChimney();

	void setPosX(const int& xpos_) { xPos = xpos_;}
	int  getPosX() const{ return xPos;}
	void setPosY(const int& ypos_) {yPos = ypos_;}

	void setPosxy(const int& xPos_, const int& yPos_);

	void checktoMap();
	void show (SDL_Renderer* des);
	SDL_Rect GetRectFrame();

private:
	int xPos;
	int yPos;
	int widthFrame;
	int heightFrame;


};


#endif
