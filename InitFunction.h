#ifndef INIT_FUNCTION_H_
#define INIT_FUNCTION_H_

#include <windows.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//AUDIO
static Mix_Chunk* gSoundFly;
static Mix_Chunk* gSoundPing;
static Mix_Chunk* gSoundScore;

//Screen
const int FRAME_PER_SECOND = 45;
const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0Xff;

//MENU
enum numMenu
{
	MENUPOS = 0,
	SCOREBOARD = 1,
	RESTART = 2, 
	BESTSCORE = 3,
	ERESTART = 4,
	EBESTSCORE = 5,
	BOARD = 6,
};

const int FPS = 40;
const int TIME_DELAY_WHEN_DIE = 200;
const int BIG_SIZE_FONT = 50;
const int SMALL_SIZE_FONT  = 35;

static int Score = 0;
static int Best = 0;
static int BestPoins[3];

//TEXT
const std::string textMenu = "FLAPPY BIRD";
const std::string textScore = "Score";
//EVENT MOUSE
const int UNPRESSED = 0;
const int PRESSED = 1;

//GROUND
const int POSY_GROUND = 540;
const int POSX_LIMITED_GROUND = 830;
static int GROUND_POS_X1 = 0;
static int GROUND_POS_X2 = 830;
static int GROUND_POS_Y = 540;

//BIRDS
const int FRAME_BIRDS = 3; 
const int POSX_START = 200;
const int POSY_START = 250;
const int POWER_FLY = 10;
const float GRAVITY = 0.8;
const int DEGREE_ROTATION = 15;

//CHIMNEY
const int POSX_CHIMNEY_RETURNED = 930;
const int AMOUNT_OF_CHIMNEY = 10;
const int POSX0_CHIMNEY = 500;
const int POSX_DISTANCE_CHIMNEY = 100;
const int POSY0_CHIMNEY_UPON = -200;
const int POSY0_CHIMNEY_BELOW = 400;
const int POSY_MOVE_CHIMNEY = 50;

enum MOVE_Y_POSITION
{
	ARRAY_MOVE_NUM = 5,
	ARRAY_MOVE_POS1 = -2,
	ARRAY_MOVE_POS2 = -1,
	ARRAY_MOVE_POS3 =  0,
	ARRAY_MOVE_POS4 =  1,
	ARRAY_MOVE_POS5 =  2,

};
const int ARRAYMOVEY[ARRAY_MOVE_NUM] = {ARRAY_MOVE_POS1,ARRAY_MOVE_POS2,
										ARRAY_MOVE_POS3,ARRAY_MOVE_POS4,
ARRAY_MOVE_POS5}; 

typedef struct Input{
	int up;
};

namespace SDLInitfunction{
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void  BestPlayer(int best[3]);
}

#endif