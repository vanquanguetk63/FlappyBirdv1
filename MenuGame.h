#ifndef MENU_GAME_H_
#define MENU_GAME_H_

#include "InitFunction.h"
#include "GameBase.h"

class MenuGame : public GameBase{
public:
	MenuGame();
	~MenuGame();

	bool LoadImg(std::string path, SDL_Renderer* screen);
	void setClip();
	void render_Clip(SDL_Renderer* des,int index);
	bool Motion(SDL_Event events, int numberMenu );

	void setWitdh(const int& width_) {width = width_;}
	int getWidth() const {return width;}

	void setHeight(const int& height_) {height = height_;}
	int getHeight() const {return height;}

	void setRectxy(const int& numberMenu);

	void setEffect(bool effect_) {effect = effect_;}
	bool getEffect(){ return effect;}

	void setType(const int& type_) {type = type_;}
	int getType() const {return type;}

	void setPress(bool pressed_) {pressed = pressed_;}
	bool getPress(){ return pressed;}
private:
	SDL_Rect gSprite[7];
	int width;
	int height;

	int type;
	bool effect;

	bool pressed;
};

#endif
