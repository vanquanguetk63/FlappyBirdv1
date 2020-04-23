#include "stdafx.h"
#include "InitFunction.h"
#include "GameBase.h"
#include "BirdsObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "MenuGame.h"

GameBase gBackground;
MenuGame gMenu;
ImpTimer gControl;
BirdsObject gBirds;
std::vector<ThreatsObject*> gListChimney;
TextObject textScreen[totalText];
TTF_Font* gFont;

int Score = 0;
int Best = 0;
int BestPoins[totalRank];
bool game_over = false;

bool Init(); 

bool loadBackground();

std::vector<ThreatsObject*> CreatListChimney();

bool InitObject();

void InitChimney(ThreatsObject* gChimney,ThreatsObject* gChimney2,int numChimney);

bool LoadMedia(int size);

void checkPoint(SDL_Rect rectBirds,SDL_Rect rectChimney);

void BestPlayer ();

void HandleEventMenu (SDL_Event g_event,SDL_Renderer* g_screen);

void Save();

void Close();

int main(int argc, char* argv[])
{
	ImpTimer fpsTimer;

	if (!Init ())
		return -1;
	if (!loadBackground ())
		return -1;
	if (!LoadMedia (BIG_SIZE_FONT))
		return -1;
	if (!InitObject())
		return -1;
	gMenu.LoadImg ("img/GameMenu.png",g_screen); //Load Menu
	gMenu.setClip ();
	ThreatsObject ground1;	//Load ground
	ThreatsObject ground2;
	ground1.LoadImgground ("img/ground.png",g_screen);
	ground1.setPosxy (GROUND_POS_X1,GROUND_POS_Y);
	ground2.LoadImgground ("img/ground.png",g_screen);
	ground2.setPosxy (GROUND_POS_X2,GROUND_POS_Y);
	//Text
	LoadMedia (BIG_SIZE_FONT);
	textScreen[MENU].SetText (textMenu);
	textScreen[MENU].LoadFromRenderText (gFont,g_screen);
	textScreen[OVER].SetText (textOver);
	textScreen[OVER].LoadFromRenderText (gFont,g_screen);
	
	bool isQuit = false;
	while (!isQuit){
		// Su kien ban phim
		while (SDL_PollEvent (&g_event)!=0)
		{
			if (g_event.type == SDL_QUIT){
				isQuit = true;
			}
			HandleEventMenu (g_event,g_screen);
			gBirds.HandleInputAction (g_event,g_screen);
		}
		SDL_SetRenderDrawColor (g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
		SDL_RenderClear (g_screen);
		gBackground.Render (g_screen,NULL); 	//RENDER ANH BACKGROUND
		fpsTimer.start ();					//chay thoi gian
		if (gControl.is_started ()){ 		//RENDER VA UPDATE CAC DOI TUONG 
			for (int num=0;num<AMOUNT_OF_CHIMNEY;num++){
				ThreatsObject* gChimney = gListChimney.at (num);
				if (gChimney!=NULL){
					if (game_over == false && gBirds.getStay() == false){
						SDL_Rect rectBirds = gBirds.GetRectFrame ();
						SDL_Rect rectChimney = gChimney->GetRectFrame ();
						gChimney->UpdateChimney ();
						if (num%2==0){
							checkPoint(rectBirds,rectChimney);
							
						}
						bool check = SDLInitfunction::CheckCollision (rectBirds,rectChimney);
						if (check){
							Mix_PlayChannel(-1,gSoundPing,0);
							gBirds.isDying (check,rectChimney);
							game_over = true;
							Save ();
							SDL_Delay (TIME_DELAY_WHEN_DIE);
						}
						std::string textScore = "SCORE ";
						std::string score = std::to_string (Score);
						textScore += score;
						textScreen[SCORE].SetText (textScore);
						textScreen[SCORE].LoadFromRenderText (gFont,g_screen);
						textScreen[SCORE].Render (g_screen,SCORE);
					} 
					if (gBirds.getStay () == false){
						gChimney->Render (g_screen,NULL);
					}
				}
			}
			gBirds.Doplayer ();
			gBirds.Show (g_screen);	
			if (gBirds.getFly ()== true) {
				Mix_PlayChannel(-1,gSoundFly,0);
				gBirds.setFly (false);
			}
			
		}
		else 
		{
			textScreen[MENU].Render(g_screen,MENU);
			gMenu.render_Clip (g_screen,MENUPOS);
		}
		ground1.UpdateGround ();
		ground2.UpdateGround ();
		ground1.Render (g_screen,NULL);
		ground2.Render (g_screen,NULL);
		if (game_over == true) {
			if (Score > Best){
				Best = Score;
			}
			gMenu.render_Clip (g_screen,SCOREBOARD);

			if (gMenu.getEffect () == true && gMenu.getType () == RESTART ){
				gMenu.render_Clip (g_screen,ERESTART);
			}
			else
			{
				gMenu.render_Clip (g_screen,RESTART);
			}
				
			if (gMenu.getEffect () == true && gMenu.getType () == BESTSCORE ){
				gMenu.render_Clip (g_screen,EBESTSCORE);
			}
			else
			{
				gMenu.render_Clip (g_screen,BESTSCORE);
			}
			
			LoadMedia (BIG_SIZE_FONT);
			textScreen[OVER].Render (g_screen,OVER);

			std::string scoreFinal = std::to_string (Score);
			textScreen[SCOREFINAL].SetText (scoreFinal);
			textScreen[SCOREFINAL].LoadFromRenderText (gFont,g_screen);
			textScreen[SCOREFINAL].Render (g_screen,SCOREFINAL);

			std::string best_ = std::to_string (Best);
			textScreen[BEST].SetText (best_);
			textScreen[BEST].LoadFromRenderText (gFont,g_screen);
			textScreen[BEST].Render (g_screen,BEST);

			if (gMenu.getPress () == true){
				gMenu.render_Clip (g_screen,BOARD);
				LoadMedia (SMALL_SIZE_FONT);

				std::string Best1 = std::to_string (BestPoins[rank1]);
				Best1+=textPTS;
				textScreen[BEST1].SetText (Best1);
				textScreen[BEST1].LoadFromRenderText (gFont,g_screen);
				textScreen[BEST1].Render (g_screen,BEST1);	

				std::string Best2 = std::to_string (BestPoins[rank2]);
				Best2+=textPTS;
				textScreen[BEST2].SetText (Best2);
				textScreen[BEST2].LoadFromRenderText (gFont,g_screen);
				textScreen[BEST2].Render (g_screen,BEST2);	

				std::string Best3 = std::to_string (BestPoins[rank3]);
				Best3+=textPTS;
				textScreen[BEST3].SetText (Best3);
				textScreen[BEST3].LoadFromRenderText (gFont,g_screen);
				textScreen[BEST3].Render (g_screen,BEST3);	
			}
		}
		SDL_RenderPresent (g_screen);
		int real_imp_time = fpsTimer.get_ticks (); // thoi gian chay het 1 lan
		int time_one_frame = 1000/FPS; //ms
		if (real_imp_time < time_one_frame){
			int delay_time = time_one_frame - real_imp_time;
			SDL_Delay(delay_time);
		}
	}
	Close ();
	return 0;
}

bool Init(){
	bool success = true;
	int ret = SDL_Init (SDL_INIT_VIDEO);
	if (ret < 0)
		return false;

	SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY,"1");
	g_window = SDL_CreateWindow ("Flappy Bird", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (g_window == NULL){
		success = false;
	}
	else{
		g_screen = SDL_CreateRenderer (g_window,-1,SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor (g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init (imgFlags)&&imgFlags))
				success = false;
		}
		if( TTF_Init() == -1 )
		{
			printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
			success = false;
		}
		if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT,2,2048 ) < 0){
			success = false;
		}
		// Load Sound
		gSoundFly = Mix_LoadWAV("audio/fap.wav");
		gSoundPing = Mix_LoadWAV("audio/fall.wav");
		gSoundScore = Mix_LoadWAV("audio/getpoint.wav");
	}
	return success;
}

bool loadBackground(){
	bool ret = gBackground.LoadImg ("img/background.png",g_screen);
	if (ret == false)
		return false;

	return true;
}

bool InitObject(){
	BestPlayer ();
	gBirds.setDegree (0);
	gBirds.SetRect (POSX_START,POSY_START);
	gBirds.LoadImg ("img/bird_sprite.png", g_screen);
	gBirds.set_clip ();
	gListChimney = CreatListChimney(); 
	if (gListChimney.size ()==0)
		return false;
	return true;
}

std::vector<ThreatsObject*> CreatListChimney()
{
	std::vector<ThreatsObject*> listChimney;
	ThreatsObject* listChimneyStatic = new ThreatsObject[AMOUNT_OF_CHIMNEY];
	
	for (int numberChimney = 0;numberChimney<AMOUNT_OF_CHIMNEY;numberChimney+=2){
		ThreatsObject* gChimney = (listChimneyStatic+numberChimney);
		ThreatsObject* gChimney2 = (listChimneyStatic+numberChimney+1);

		if (gChimney!=NULL&&gChimney2!=NULL){
			InitChimney(gChimney,gChimney2,numberChimney);
			listChimney.push_back (gChimney);
			listChimney.push_back (gChimney2);
		}
	}
	return listChimney;
}

void InitChimney(ThreatsObject* gChimney,ThreatsObject* gChimney2,int numChimney){
	
	int randomNumberY = rand()%5;
	int moveY = ARRAYMOVEY[randomNumberY];

	gChimney->LoadImgchimney ("img/chimney_.png",g_screen);
	gChimney->setPosX (numChimney*POSX_DISTANCE_CHIMNEY+POSX0_CHIMNEY);
	gChimney->setPosY (POSY0_CHIMNEY_UPON+POSY_MOVE_CHIMNEY*moveY);
	
	gChimney2->LoadImgchimney ("img/chimney.png",g_screen);
	gChimney2->setPosX (numChimney*POSX_DISTANCE_CHIMNEY+POSX0_CHIMNEY);
	gChimney2->setPosY (POSY0_CHIMNEY_BELOW+POSY_MOVE_CHIMNEY*moveY);
}

void HandleEventMenu(SDL_Event g_event,SDL_Renderer* g_screen){
	if (g_event.type == SDL_KEYDOWN){
		switch (g_event.key.keysym.sym ){
		case SDLK_SPACE:
			if (gControl.is_started () == false){
				gControl.start();	
			}
			if (gMenu.getPress () == true){
				gMenu.setPress (false);
			}
			break;

		default:
			break;
		}
	}
	if (g_event.type == SDL_MOUSEBUTTONDOWN ){
		if (g_event.button.button == SDL_BUTTON_LEFT && gMenu.getPress ()  == false ){
			if (gMenu.Motion (g_event,RESTART) == true  ){
				game_over = false;
				gBirds.setIsDied (false);
				gBirds.setStay (true);
				gListChimney.erase (gListChimney.begin (),gListChimney.begin()+AMOUNT_OF_CHIMNEY);
				Score = 0;
				InitObject ();
			}
			else if (gMenu.Motion (g_event,BESTSCORE) == true )
			{
				gMenu.setPress (true);
				gMenu.render_Clip (g_screen,BOARD);
			}
		}
	}
	if (g_event.type == SDL_MOUSEMOTION && game_over == true  && gMenu.getPress ()  == false){
		if (gMenu.Motion(g_event, RESTART) == true ){
			gMenu.setEffect (true);
			gMenu.setType (RESTART);
		}
		else if (gMenu.Motion(g_event, BESTSCORE) == true ){
			gMenu.setEffect (true);
			gMenu.setType (BESTSCORE);
		}
		else
		{
			gMenu.setEffect (false);
		}
	}
}

void checkPoint(SDL_Rect rectBirds,SDL_Rect rectChimney){
	if (rectChimney.x == rectBirds.x){
		Score++;
		Mix_PlayChannel(-1, gSoundScore,0);
	}
}

bool LoadMedia (int size){
	gFont = TTF_OpenFont ("font/FB.ttf",size);
	if (gFont==NULL)
		return false;
	return true;
}

void BestPlayer (){
	std::ifstream pfile;
	pfile.open ("Best.txt");
	for (int i=0;i<3;i++){
		pfile >> BestPoins[i];
	}
	pfile.close ();
	std::sort(BestPoins,BestPoins+2);
	Best = BestPoins[2];
}

void AddPoints(){
	if (Score == BestPoins[2] || Score ==BestPoins[1] || Score == BestPoins[0] )
		return;
	if (Score > BestPoins[2]){
		BestPoins[0] = BestPoins[1];
		BestPoins[1] = BestPoins[2];
		BestPoins[2] = Score;
	}
	else if (Score > BestPoins[1]){
		BestPoins[0] = BestPoins[1];
		BestPoins[1] = Score;
	}
	else if (Score > BestPoins[0]) BestPoins [0] = Score;
}

void Save(){
	AddPoints();
	std::ofstream pfileout;
	pfileout.open ("Best.txt");
	for (int i=0;i<3;i++){
		pfileout << BestPoins[i];
		pfileout << " ";
	}
	pfileout.close ();
}

void Close(){

	gBackground.Free ();
	gMenu.Free ();

	TTF_CloseFont( gFont );
	gFont = NULL;

	textScreen->Free ();

	Mix_FreeChunk(gSoundFly);
	Mix_FreeChunk(gSoundPing);
	Mix_FreeChunk(gSoundScore);

	SDL_DestroyRenderer (g_screen);
	g_screen = NULL;
	SDL_DestroyWindow (g_window);
	g_window = NULL;
	IMG_Quit ();
	Mix_Quit();
	SDL_Quit();
}


