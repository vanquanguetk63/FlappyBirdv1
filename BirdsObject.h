#ifndef CHIMNEY_OBJECT_H_
#define CHIMNEY_OBJECT_H_
#include "GameBase.h"

class BirdsObject : public GameBase{
public:
	BirdsObject();
	~BirdsObject();


	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clip();
	void Doplayer();
	void CheckToMap();
	SDL_Rect GetRectFrame();
	void setDegree(double degree_) {degree = degree_;}
	void isDying(bool Check, SDL_Rect chimney);
	float getPosY() const {return yPos;}
	void checkMoving(SDL_Rect* chimney);

	bool getIsDied() const {return isDied;}
	void setIsDied(const bool& isDied_) {isDied = isDied_;}

	void setYvalue(const int& yval_) {yValue = yval_;}
	float getYvalue() const {return yValue;}

	void setStay(const bool& stay_) {stayed = stay_;}
	bool getStay() const {return stayed;}

	void setFly(const bool& fly_) {fly = fly_;}
	bool getFly() const {return fly;}

private:
	float xPos;
	float yPos;
	float xValue;
	float yValue;
	int widthFrame;
	int heightFrame;

	SDL_Rect frameChimney[FRAME_BIRDS];
	int frame;
	Input inputType;

	double degree;

	bool isDied;
	bool stayed;
	bool fly;

};


#endif
