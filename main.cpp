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
BirdsObject gBirds;
std::vector<ThreatsObject*> gListChimney;
ImpTimer gControl;
TextObject textScreen[8];
TTF_Font* gFont;

bool game_over = false;


//Khoi tao man hinh,tao Font,Audio, vv
bool Init(); 
//Load Anh nen
bool loadBackground();
//Tao danh sach chimney
std::vector<ThreatsObject*> CreatListChimney();
//Dong Cua so
void Close();

void InitObject();

void InitChimney(ThreatsObject* gChimney,ThreatsObject* gChimney2,int index);

bool LoadMedia(int size);

void checkPoint(SDL_Rect rectBirds,SDL_Rect rectChimney);

void BestPlayer ();

void HandleEventMenu (SDL_Event g_event,SDL_Renderer* g_screen);

void Save();

int main(int argc, char* argv[])
{
	
	//TAO OBJECT THOI GIAN
	ImpTimer fpsTimer;

	if (Init () == false)
		return -1;
	if (loadBackground () == false)
		return -1;
	if (LoadMedia (50) == false)
		return -1;

	gMenu.LoadImg ("img/GameMenu.png",g_screen);
	gMenu.setClip ();

	InitObject();

	ThreatsObject ground1;
	ThreatsObject ground2;
	ground1.LoadImgground ("img/ground.png",g_screen);
	ground1.setPosxy (GROUND_POS_X1,GROUND_POS_Y);
	ground2.LoadImgground ("img/ground.png",g_screen);
	ground2.setPosxy (GROUND_POS_X2,GROUND_POS_Y);


	//Text
	textScreen[0].SetText ("HELOO");
	textScreen[0].LoadFromRenderText (gFont, g_screen);
	

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
		//RENDER ANH BACKGROUND
		gBackground.Render (g_screen,NULL);

		
		fpsTimer.start ();

		if (gControl.is_started ()){
			//RENDER VA UPDATE CAC DOI TUONG 
			for (int i=0;i<10;i++){
				ThreatsObject* gChimney = gListChimney.at (i);
				if (gChimney!=NULL){
					if (game_over == false ){
						SDL_Rect rectBirds = gBirds.GetRectFrame ();
						SDL_Rect rectChimney = gChimney->GetRectFrame ();
						gChimney->UpdateChimney ();

						if (i%2==0){
							checkPoint(rectBirds,rectChimney);
						}
					
						bool check = SDLInitfunction::CheckCollision (rectBirds,rectChimney);
						if (check){
							Mix_PlayChannel(-1,gSoundPing,0);
							gBirds.isDying (check,rectChimney);
							game_over = true;
							Save ();
							SDL_Delay (200);
						}
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
			textScreen[0].Render (g_screen,0);
			gMenu.render_Clip (g_screen,MENUPOS);
		}

		ground1.UpdateGround ();
		ground2.UpdateGround ();
		ground1.Render (g_screen,NULL);
		ground2.Render (g_screen,NULL);


		if (game_over == true) {
			if (Points > Best){
				Best = Points;
			}
			gMenu.render_Clip (g_screen,SCOREBOARD);

			if (gMenu.getEffect () == true && gMenu.getType () == 0 ){
					gMenu.render_Clip (g_screen,ERESTART);
			}
			else
			{
				gMenu.render_Clip (g_screen,RESTART);
			}
				
			if (gMenu.getEffect () == true && gMenu.getType () == 1 ){
				gMenu.render_Clip (g_screen,EBESTSCORE);
			}
			else
			{
				gMenu.render_Clip (g_screen,BESTSCORE);
			}
				
			if (gMenu.getPress () == true){
				
				gMenu.render_Clip (g_screen,BOARD);
				LoadMedia (35);
				
			}
		}
	

		SDL_RenderPresent (g_screen);

		int real_imp_time = fpsTimer.get_ticks (); // thoi gian chay het 1 lan
		int time_one_frame = 1000/40; //ms
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

		gSoundFly = Mix_LoadWAV("audio/fap.wav");
		gSoundPing = Mix_LoadWAV("audio/fall.wav");
		gSoundScore = Mix_LoadWAV("audio/getpoint.wav");
	}
	return success;
}

// Load hinh nen
bool loadBackground(){
	bool ret = gBackground.LoadImg ("img/background.png",g_screen);
	if (ret == false)
		return false;

	return true;
}




std::vector<ThreatsObject*> CreatListChimney()
{
	std::vector<ThreatsObject*> listChimney;
	ThreatsObject* listChimneyStatic = new ThreatsObject[10];
	
	for (int i = 0;i<10;i+=2){
		ThreatsObject* gChimney = (listChimneyStatic+i);
		ThreatsObject* gChimney2 = (listChimneyStatic+i+1);

		if (gChimney!=NULL&&gChimney2!=NULL){
			InitChimney(gChimney,gChimney2,i);
			listChimney.push_back (gChimney);
			listChimney.push_back (gChimney2);
		}
	}
	return listChimney;
}


void InitChimney(ThreatsObject* gChimney,ThreatsObject* gChimney2,int index){
	
	int randomNumberY = rand()%5;
	int moveY = ARRAYMOVEY[randomNumberY];

	gChimney->LoadImgchimney ("img/chimney_.png",g_screen);
	gChimney->setPosX (index*100+500);
	gChimney->setPosY (-200+50*moveY);
	
	gChimney2->LoadImgchimney ("img/chimney.png",g_screen);
	gChimney2->setPosX (index*100+500);
	gChimney2->setPosY (400+50*moveY);

	
}

void Close(){
	gBackground.Free ();
	gMenu.Free ();
	
	SDL_DestroyRenderer (g_screen);
	g_screen = NULL;
	SDL_DestroyWindow (g_window);
	g_window = NULL;

	IMG_Quit ();
	SDL_Quit();
}

bool LoadMedia (int size){
	gFont = TTF_OpenFont ("font/FB.ttf",size);
	if (gFont==NULL)
		return false;
	return true;
}
void checkPoint(SDL_Rect rectBirds,SDL_Rect rectChimney){
	if (rectChimney.x == rectBirds.x){
		Points++;
		Mix_PlayChannel(-1, gSoundScore,0);
	}

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

void Save(){
	if (Points >= BestPoins[2]){
		BestPoins[0] = BestPoins[1];
		BestPoins[1] = BestPoins[2];
		BestPoins[2] = Points;
	}
	else if (Points >= BestPoins[1]){
		BestPoins[0] = BestPoins[1];
		BestPoins[1] = Points;
	}
	else if (Points >= BestPoins[0]) BestPoins [0] = Points;


	std::ofstream pfileout;
	pfileout.open ("Best.txt");
	for (int i=0;i<3;i++){
		pfileout << BestPoins[i];
		pfileout << " ";
	}
	pfileout.close ();
}


void InitObject(){

	BestPlayer ();
	//Tao doi tuong Bird

	gBirds.SetRect (POSX_START,POSY_START);
	gBirds.LoadImg ("img/bird_sprite.png", g_screen);
	gBirds.set_clip ();


	//Tao doi tuong dat nen

	//DANH SACH CHIMNEY
	gListChimney = CreatListChimney(); 

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

	if (g_event.type == SDL_MOUSEBUTTONDOWN){
		if (g_event.button.button == SDL_BUTTON_LEFT && game_over == true ){

			if (gMenu.Motion (g_event,RESTART) == true ){
				game_over = false;
				gBirds.setIsDied (false);
				gBirds.setStay (true);
				gListChimney.erase (gListChimney.begin (),gListChimney.begin()+10);
				Points = 0;
				InitObject ();
			}
			else if (gMenu.Motion (g_event,BESTSCORE) == true )
			{
				gMenu.setPress (true);
				gMenu.render_Clip (g_screen,BOARD);
			}
		}
	}

	if (g_event.type == SDL_MOUSEMOTION && game_over == true){
		if (gMenu.Motion(g_event, RESTART) == true ){
			gMenu.setEffect (true);
			gMenu.setType (0);
		}


		else if (gMenu.Motion(g_event, BESTSCORE) == true ){
			gMenu.setEffect (true);
			gMenu.setType (1);
		}
		else
		{
			gMenu.setEffect (false);
		}
	}
}






