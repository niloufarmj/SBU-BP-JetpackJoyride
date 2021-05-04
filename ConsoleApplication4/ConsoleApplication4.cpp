#include "stdafx.h"
#include "SBDL.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

enum state {
	start, play, home, pause, gameOver, coinEvent, lazerEvent, missleEvent, speedtokenEvent, zapperEvent, gravitytokenEvent
};
enum barrySituation {
	barryRun, barryWalk, barryFly, barryFall, gravityBarryFly, gravityBarryFall, gravityBarryWalkDown, gravityBarryWalkUp, gravityBarryRunDown, gravityBarryRunUp, baryGoFast
};
enum backgroundTypes {
	 firstBack, otherBack, wareBack
};
enum zapperShowing {
	firstZap, secondZap, thirdZap, fourthZap
};
enum homeMenu {
	poster1, poster2, poster3, changeBarry
};
enum missleShowing {
	missleFar, missleNear, missleIn
};
enum laserShowing {
	nonactive, active1, active2
};

struct core {
	int x;
	int y;
};
struct zapper {
	Texture first;
	Texture second;
	Texture third;
	Texture fourth;
	int x;
	int y;
};
struct lazer {
	Texture nonactive;
	Texture active1;
	Texture active2;
	int existance;
	int x;
	int y;
	SDL_Rect Rect;
};
struct backGround {
	Texture pic;
	int x;
};
struct missle {
	Texture picArray[6];
	int x;
	int y;
};
struct speedToken {
	Texture pic1;
	Texture pic2;
	Texture pic3;
	Texture pic4;
	int x;
	int y;
};

state chum;

core barryLocation;
core backLocation;
core redWarLoc;
core yellowWarLoc;
core rand_redWarLoc_1;
core rand_yellowWarLoc_1;
core rand_redWarLoc_2;
core rand_yellowWarLoc_2;
core barryPoster;
core menuClickCore;
core menuLocation;
core gToken;

zapper myZapper;
speedToken myToken;
backgroundTypes how_is_back;
zapperShowing how_is_zapper;
homeMenu how_is_menu;
missleShowing how_is_missle;
lazer mylazer[6];
missle myMissle;
missle randomMissle1;
missle randomMissle2;
zapper horizentalZap;
zapper verticalZap;
zapper angledZap;
zapper zappersArray[3];
state eventsArray[6] = { missleEvent , gravitytokenEvent , missleEvent , speedtokenEvent , missleEvent ,lazerEvent };
barrySituation how_is_barry;
laserShowing how_is_laser;

int zapper_y[3] = { 35 , 150 , 280 };
int which_zapper_y;
int which_zapper;
int which_zapper_x;
const int window_width = 800;
const int window_height = 460;
const int FPS = 60; //frame per second
const int delay = 1000 / FPS; //delay we need at each frame
int barryVelocity_y;
int shetab;
int backVelocity = -7;
int zapperVelocity = -7;
int whichBack;
int walkingCounter;
int zapperCounter;
int menuCounter;
int missleCounter;
int gameoverCounter;
int laserCounter;
int tokenCounter;
int GtokenConter;
int barryPosterSize_x;
int barryPosterSize_y;
int accelerationCounter;
int tempToken_y;
int lazer_y[6] = { 30, 105 , 180 , 255 , 330 , 405 };
int which_lazer_y;
int elapsedTime, startTime;
int randomEvents;
int soundCounter;
int notForgetCounter;
int score;

bool finishFlag = false;
bool gameStart = false;
bool pausePage = false;
bool clickAnyWhereFlag = true;
bool flyStopFlag;
bool youngBarryFlag = false;
bool oldBarryFlag = true;
bool changeBarryFlag = false;
bool chooseBarryFlag = false;
bool myMissleFlag;
bool newLaserFlag = true;
bool tokenFlag = false;
bool gravitySituation = false;
bool flyGravityFlag = false;
bool fallGravityFlag = false;
bool lazerMainFlag;
bool missleMainFlag;
bool zapperMainFlag;
bool speedTokenMainFlag;
bool gravityTokenMainFlag;
bool soundFlag;
bool musicFlag;

SDL_Rect pausePageHomeRect;
SDL_Rect barryRect = { barryLocation.x, barryLocation.y, 25, 32 };
SDL_Rect windowRect = { 0 , 0, window_width, window_height };
SDL_Rect homeBarryRect = { barryPoster.x, barryPoster.y, 500, 260 };
SDL_Rect pauseRect = { 750 , 20 , 20 , 30 };
SDL_Rect resumeRect = { 70, 200, 200 , 70 };
SDL_Rect quitRect = { 560 , 210 , 220 , 60 };
SDL_Rect retryRect = { 530, 200, 200, 70 };
SDL_Rect backRect;
SDL_Rect menuRect;
SDL_Rect menuClickRect = { 750, 0 , 60 , 70 };
SDL_Rect clickAnyWhereRect = { 100 , 400 , 600 , 40 };
SDL_Rect anywhere1;
SDL_Rect anywhere2;
SDL_Rect anywhere3;
SDL_Rect anywhere4;
SDL_Rect myZapperRect;
SDL_Rect warningRect;
SDL_Rect missleRect;
SDL_Rect changeBarryRect = { 560 , 140 , 220 , 60 };
SDL_Rect oldRect = { 200 , 150 , 200 , 200 };
SDL_Rect youngRect = { 450 , 150 , 200 , 200 };
SDL_Rect chooseTextRect = { 200 , 50 , 450 , 50 };
SDL_Rect oldTextRect = { 200 , 100 , 200 , 50 };
SDL_Rect youngTextRect = { 450 , 100 , 200 , 50 };
SDL_Rect gameoverRetryRect = { 100 , 300 , 250 , 100 };
SDL_Rect gameoverHomeRect = { 450 , 300 , 250 , 100 };
SDL_Rect myLazerRect;
SDL_Rect myTokenRect;
SDL_Rect GTokenRect;
SDL_Rect showPausedRect = { 200 , 0 , 400 , 50 };

backGround backArray[12];
backGround startPage;
backGround labStart;
backGround lab1;
backGround lab2;
backGround sectorStart;
backGround sector1;
backGround sector2;
backGround volcanoStart;
backGround volcano1;
backGround volcano2;
backGround warehouseStart;
backGround warehouse;

Texture oldBarryRunPic;
Texture oldBarryWalkPic;
Texture oldBarryRiseJet;
Texture oldBarryFallPic;
Texture oldBarryGoFast;
Texture pausePic;
Texture retryPic;
Texture quitPic;
Texture resumePic;
Texture blackBack;
Texture homePic;
Texture homePic2;
Texture menuClick;
Texture homePageMenu;
Texture firstP;
Texture firstP2;
Texture secondP;
Texture secondP2;
Texture clickAnyWhere1;
Texture clickAnyWhere2;
Texture clickAnyWhere3;
Texture darkBlackBack;
Texture yellowWarning;
Texture redWarning;
Texture youngBarryRunPic;
Texture youngBarryWalkPic;
Texture youngBarryRiseJet;
Texture youngBarryFallPic;
Texture youngBarryGoFast;
Texture oldText;
Texture youngText;
Texture chooseText;
Texture homePicClick;
Texture gravityBarryWalkDownPic;
Texture gravityBarryRunDownPic;
Texture gravityBarryWalkUpPic;
Texture gravityBarryRunUpPic;
Texture gravityBarryFlyPic;
Texture gravityBarryFallPic;
Texture gravityToken;
Texture gravityToken1;
Texture gravityToken2;
Texture gravityToken3;
Texture gravityToken4;
Texture gravityToken5;
Texture gravityToken6;
Texture gravityToken7;
Texture gravityToken8;
Texture gravityToken9;
Texture gravityToken10;
Texture yourScoreText;
Texture showPaused;
Texture fontTexture;

Sound* zapperSound;
Sound* missleWarninSound;
Sound* missleLounchSound;
Sound* gravityFlySound;
Sound* gravityFallSound;
Sound* jetSound;
Music* gameMusic;
Font* scoreFont;

void what_to_do(state);
void play_game();
void initializer();
void happenings();
void updateBarry();
void drawBarry(barrySituation);
void updateBackGround();
void drawBackGround(backgroundTypes);
void updateZapper();
void drawZapper(zapperShowing);
void initZapper();
void updateMenu();
void drawMenu(homeMenu);
void inFlying();
void updateMissle();
void drawMissle(missleShowing);
void mainDraw();
void pausePageFun();
void gameOverPageFun();
void updateGameOverPage();
void drawGameOverPage();
void updateLaser();
void drawLaser(laserShowing);
void updateSpeedToken();
void drawSpeedToken();
void updateGravityToken();
void drawGravityToken();
void gravityFlyFall();
void zapperFun();
void missleFun();
void lazerFun();
void gravityFun();
void speedFun();

int main()
{
	srand(time(NULL));
	SBDL::InitEngine("Jetpack_Joyride", window_width, window_height);

	labStart.pic = SBDL::loadTexture("assets/pic/back/Lab Start.png");
	lab1.pic = SBDL::loadTexture("assets/pic/back/Lab1.png");
	lab2.pic = SBDL::loadTexture("assets/pic/back/Lab2.png");
	sectorStart.pic = SBDL::loadTexture("assets/pic/back/Sector Start.png");
	sector1.pic = SBDL::loadTexture("assets/pic/back/Sector1.png");
	sector2.pic = SBDL::loadTexture("assets/pic/back/Sector2.png");
	warehouseStart.pic = SBDL::loadTexture("assets/pic/back/warehouse Start.png");
	warehouse.pic = SBDL::loadTexture("assets/pic/back/warehouse.png");
	volcanoStart.pic = SBDL::loadTexture("assets/pic/back/volcano Start.png");
	volcano1.pic = SBDL::loadTexture("assets/pic/back/volcano1.png");
	volcano2.pic = SBDL::loadTexture("assets/pic/back/volcano2.png");
	oldBarryRunPic = SBDL::loadTexture("assets/pic/barry/barry.png");
	oldBarryWalkPic = SBDL::loadTexture("assets/pic/barry/barry2.png");
	oldBarryRiseJet = SBDL::loadTexture("assets/pic/barry/barry3.png");
	oldBarryFallPic = SBDL::loadTexture("assets/pic/barry/barry4.png");
	oldBarryGoFast = SBDL::loadTexture("assets/pic/speedToken/fast barry.png");
	youngBarryRunPic = SBDL::loadTexture("assets/pic/barry/my barry.png");
	youngBarryWalkPic = SBDL::loadTexture("assets/pic/barry/my barry2.png");
	youngBarryRiseJet = SBDL::loadTexture("assets/pic/barry/my barry3.png");
	youngBarryFallPic = SBDL::loadTexture("assets/pic/barry/my barry4.png");
	gravityBarryWalkDownPic = SBDL::loadTexture("assets/pic/barry/gg1.png");
	gravityBarryRunDownPic = SBDL::loadTexture("assets/pic/barry/gg2.png");
	gravityBarryWalkUpPic = SBDL::loadTexture("assets/pic/barry/gg3.png");
	gravityBarryRunUpPic = SBDL::loadTexture("assets/pic/barry/gg4.png");
	gravityBarryFlyPic = SBDL::loadTexture("assets/pic/barry/ggup.png");
	gravityBarryFallPic = SBDL::loadTexture("assets/pic/barry/ggdown.png");
	gravityToken = SBDL::loadTexture("assets/pic/menu/gravity_token.png");
	gravityToken1 = SBDL::loadTexture("assets/pic/menu/gravity_token1.png");
	gravityToken2 = SBDL::loadTexture("assets/pic/menu/gravity_token2.png");
	gravityToken3 = SBDL::loadTexture("assets/pic/menu/gravity_token3.png");
	gravityToken4 = SBDL::loadTexture("assets/pic/menu/gravity_token4.png");
	gravityToken5 = SBDL::loadTexture("assets/pic/menu/gravity_token5.png");
	gravityToken6 = SBDL::loadTexture("assets/pic/menu/gravity_token6.png");
	gravityToken7 = SBDL::loadTexture("assets/pic/menu/gravity_token7.png");
	gravityToken8 = SBDL::loadTexture("assets/pic/menu/gravity_token8.png");
	gravityToken9 = SBDL::loadTexture("assets/pic/menu/gravity_token9.png");
	gravityToken10 = SBDL::loadTexture("assets/pic/menu/gravity_token10.png");
	verticalZap.first = SBDL::loadTexture("assets/pic/zappers/v1.png");
	verticalZap.second = SBDL::loadTexture("assets/pic/zappers/v2.png");
	verticalZap.third = SBDL::loadTexture("assets/pic/zappers/v3.png");
	verticalZap.fourth = SBDL::loadTexture("assets/pic/zappers/v4.png");
	horizentalZap.first = SBDL::loadTexture("assets/pic/zappers/h1.png");
	horizentalZap.second = SBDL::loadTexture("assets/pic/zappers/h2.png");
	horizentalZap.third = SBDL::loadTexture("assets/pic/zappers/h3.png");
	horizentalZap.fourth = SBDL::loadTexture("assets/pic/zappers/h4.png");
	angledZap.first = SBDL::loadTexture("assets/pic/zappers/d1.png");
	angledZap.second = SBDL::loadTexture("assets/pic/zappers/d2.png");
	angledZap.third = SBDL::loadTexture("assets/pic/zappers/d3.png");
	angledZap.fourth = SBDL::loadTexture("assets/pic/zappers/d4.png");
	for (int i = 0; i < 6; i++)
	{
		mylazer[i].nonactive = SBDL::loadTexture("assets/pic/lazer/laser_noneactive.png");
		mylazer[i].active1 = SBDL::loadTexture("assets/pic/lazer/laser_active1.png");
		mylazer[i].active2 = SBDL::loadTexture("assets/pic/lazer/laser_active2.png");
	}
	pausePic = SBDL::loadTexture("assets/Pause.png");
	blackBack = SBDL::loadTexture("assets/blackBack.png", 900);
	darkBlackBack = SBDL::loadTexture("assets/blackBack.png");
	resumePic = SBDL::loadTexture("assets/pic/menu/resume.png");
	retryPic = SBDL::loadTexture("assets/pic/menu/retry.png");
	quitPic = SBDL::loadTexture("assets/pic/menu/quit.png");
	homePic = SBDL::loadTexture("assets/pic/menu/pauseb.png");
	homePic2 = SBDL::loadTexture("assets/pic/menu/pausea.png");
	startPage.pic = SBDL::loadTexture("assets/pic/back/startPage.jpg");
	menuClick = SBDL::loadTexture("assets/pic/menu/menuClick.png");
	homePageMenu = SBDL::loadTexture("assets/pic/menu/menu.png");
	firstP = SBDL::loadTexture("assets/pic/parallex/First P.png");
	firstP2 = SBDL::loadTexture("assets/pic/parallex/First P2.png");
	secondP = SBDL::loadTexture("assets/pic/parallex/First P.png");
	secondP2 = SBDL::loadTexture("assets/pic/parallex/First P2.png");
	clickAnyWhere1 = SBDL::loadTexture("assets/pic/menu/clickanywhere.png");
	clickAnyWhere2 = SBDL::loadTexture("assets/pic/menu/clickanywhere.png" , 100);
	clickAnyWhere3 = SBDL::loadTexture("assets/pic/menu/clickanywhere.png" , 50);
	myMissle.picArray[0] = SBDL::loadTexture("assets/pic/missle/missle (1).png");
	myMissle.picArray[1] = SBDL::loadTexture("assets/pic/missle/missle (2).png");
	myMissle.picArray[2] = SBDL::loadTexture("assets/pic/missle/missle (3).png");
	myMissle.picArray[3] = SBDL::loadTexture("assets/pic/missle/missle (4).png");
	myMissle.picArray[4] = SBDL::loadTexture("assets/pic/missle/missle (5).png");
	myMissle.picArray[5] = SBDL::loadTexture("assets/pic/missle/missle (6).png");
	redWarning = SBDL::loadTexture("assets/pic/missle/1m.png");
	yellowWarning = SBDL::loadTexture("assets/pic/missle/2m.png");
	oldText = SBDL::loadTexture("assets/pic/menu/old text.png");
	youngText = SBDL::loadTexture("assets/pic/menu/young text.png");
	chooseText = SBDL::loadTexture("assets/pic/menu/choose barry.png");
	homePicClick = SBDL::loadTexture("assets/pic/menu/home.png.");
	myToken.pic1 = SBDL::loadTexture("assets/pic/speedToken/speed token.png");
	myToken.pic2 = SBDL::loadTexture("assets/pic/speedToken/speed token2.png");
	myToken.pic3 = SBDL::loadTexture("assets/pic/speedToken/speed token3.png");
	myToken.pic4 = SBDL::loadTexture("assets/pic/speedToken/speed token4.png");
	zapperSound = SBDL::loadSound("assets/sound/zapper.wav");
	missleWarninSound = SBDL::loadSound("assets/sound/missile_warning.wav");
	missleLounchSound = SBDL::loadSound("assets/sound/missile_launch.wav");
	gravityFlySound = SBDL::loadSound("assets/sound/grav_change_1.wav");
	gravityFallSound = SBDL::loadSound("assets/sound/grav_change_2.wav");
	jetSound = SBDL::loadSound("assets/sound/jetpack_se.wav");
	yourScoreText = SBDL::loadTexture("assets/pic/menu/your score.png");
	gameMusic = SBDL::loadMusic("assets/sound/my_music.wav");
	showPaused = SBDL::loadTexture("assets/pic/menu/paused.png");
	scoreFont = SBDL::loadFont("assets/font/Jetpackia.ttf" , 60);

	backArray[0] = startPage;
	backArray[1] = sector2;
	backArray[2] = sector1;
	backArray[3] = sectorStart;
	backArray[4] = labStart;
	backArray[5] = lab1;
	backArray[6] = lab2;
	backArray[7] = volcanoStart;
	backArray[8] = volcano1;
	backArray[9] = volcano2;
	backArray[10] = warehouseStart;
	backArray[11] = warehouse;

	zappersArray[0] = angledZap;
	zappersArray[1] = horizentalZap;
	zappersArray[2] = verticalZap;

	initializer();
	happenings();
	SBDL::playMusic(gameMusic, -1);
	while (SBDL::isRunning())
	{
		startTime = SBDL::getTime();
		SBDL::clearRenderScreen();
		
		what_to_do(chum);
		
		SBDL::updateRenderScreen();
		elapsedTime = SBDL::getTime() - startTime;
		if (elapsedTime < delay)
			SBDL::delay(delay - elapsedTime);
	}
}
void mainDraw()
{
	SBDL::clearRenderScreen();
	SBDL::updateEvents();
	updateBackGround();
	updateBarry();
	updateZapper();
	drawBackGround(how_is_back);
	
	drawZapper(how_is_zapper);
	zapperFun();
	missleFun();
	lazerFun();
	gravityFun();
	speedFun();
	drawBarry(how_is_barry);
	SBDL::showTexture(pausePic, pauseRect);
	SBDL::updateRenderScreen();
}
void what_to_do(state chum)
{
	switch (chum)
	{
	case play:
		play_game();
		break;
	case home:
		updateMenu();
		drawMenu(how_is_menu);
		break;
	case pause:
		pausePageFun();
		break;
	case gameOver:
		gameOverPageFun();
		break;
	}
}
void initializer()
{
	finishFlag = false;
	gameStart = false;
	pausePage = false;
	clickAnyWhereFlag = true;
	youngBarryFlag = false;
	oldBarryFlag = true;
	changeBarryFlag = false;
	chooseBarryFlag = false;
	newLaserFlag = true;
	tokenFlag = false;
	gravitySituation = false;
	flyGravityFlag = false;
	fallGravityFlag = false;
	soundFlag = true;
	musicFlag = true;

	chum = home;

	walkingCounter = 0;
	zapperCounter = 0;

	score = 0;

	barryLocation.x = 0;
	barryLocation.y = 380;
	barryVelocity_y = 1;

	for (int i = 0; i < 11; i++)
	{
		if (i == 0)
			backArray[i].x = 0;
		else
			backArray[i].x = 800 + 2048 * (i - 1);
	}
	
	shetab = 1;
	
	barryPoster.x = 100;
	barryPoster.y = 50;
	barryPosterSize_x = 600;
	barryPosterSize_y = 300;
	menuClickCore.x = 750;
	menuClickCore.y = 0;
	menuCounter = 0;
	menuLocation.x = 240;
	menuLocation.y = 0;

	myZapper.x = -200;
	myMissle.x = -200;
	myToken.x = -200;
	gToken.x = -200;

	barryRect = { barryLocation.x, barryLocation.y, 50, 70 };
}
void happenings()
{
	randomEvents = rand() % 6;
	switch (eventsArray[randomEvents])
	{
	case lazerEvent:
		lazerMainFlag = true;
		//newLaserFlag = true;
		laserCounter = 0;
		break;
	case missleEvent:
		missleMainFlag = true;
		break;
	/*case zapperEvent:
		zapperMainFlag = true;
		break;*/
	case speedtokenEvent:
		speedTokenMainFlag = true;
		break;
	case gravitytokenEvent:
		gravityTokenMainFlag = true;
		break;
	}
}
void play_game()
{
	mainDraw();
	score++;
	if (SBDL::mouseInRect(pauseRect))
		chum = pause;
	if (SBDL::hasIntersectionRect(barryRect, missleRect) && gravitySituation == false)
		chum = gameOver;
	if (SBDL::hasIntersectionRect(barryRect, myZapperRect) && gravitySituation == false)
	{
		if (which_zapper == 1 || which_zapper == 2)
			chum = gameOver;
		else
		{
			SDL_Rect angledZapper1 = { myZapper.x + 80 , myZapper.y , 40 , 40 };
			SDL_Rect angledZapper2 = { myZapper.x + 40 , myZapper.y + 40 , 40 , 40};
			SDL_Rect angledZapper3 = { myZapper.x , myZapper.y + 80 , 40 , 40};
			if (SBDL::hasIntersectionRect(barryRect, angledZapper1) || SBDL::hasIntersectionRect(barryRect, angledZapper2) || SBDL::hasIntersectionRect(barryRect, angledZapper3))
				chum = gameOver;
		}
	}
	if (SBDL::hasIntersectionRect(barryRect, missleRect) && gravitySituation == true)
	{
		gravitySituation = false;
		youngBarryFlag = true;
	}
	if (SBDL::hasIntersectionRect(barryRect, myZapperRect) && gravitySituation == true)
	{
		gravitySituation = false;
		youngBarryFlag = true;
	}
	if (SBDL::hasIntersectionRect(barryRect, GTokenRect))
	{
		gravitySituation = true;
		youngBarryFlag = false;
		oldBarryFlag = false;
		barryLocation.y = 380;
		//how_is_barry = gravityBarryWalkDown;
		SBDL::updateEvents();
	}
	/*for (int i = 0; i < 5; i++)
	{
		if (SBDL::hasIntersectionRect(barryRect, mylazer[i].Rect) && (how_is_laser == active1 || how_is_laser == active2) && gravitySituation == false)
			chum = gameOver;
		if (SBDL::hasIntersectionRect(barryRect, mylazer[i].Rect) && (how_is_laser == active1 || how_is_laser == active2) && gravitySituation == true)
		{
			gravitySituation = false;
			youngBarryFlag = true;
		}
	}	*/
	else if (SBDL::hasIntersectionRect(barryRect, myTokenRect))
		tokenFlag = true;
	how_is_barry = baryGoFast;
}
void updateBarry()
{
	SBDL::updateEvents();
	if (!gravitySituation)
	{
		if (barryLocation.x < 110)
		{
			barryLocation.x += 1;

			if (walkingCounter % 12 < 6 && barryLocation.y >= 380)
			{
				how_is_barry = barryWalk;
				walkingCounter++;
			}
			else if (walkingCounter % 12 >= 6 && barryLocation.y >= 380)
			{
				how_is_barry = barryRun;
				walkingCounter++;
				inFlying();
			}
			inFlying();
		}
		if (walkingCounter % 12 < 6 && barryLocation.y >= 380)
		{
			how_is_barry = barryWalk;
			walkingCounter++;
		}
		else if (walkingCounter % 12 >= 6 && barryLocation.y >= 380)
		{
			how_is_barry = barryRun;
			walkingCounter++;
		}
		inFlying();
	}
	else
	{
		gravityFlyFall();
	}
}
void drawBarry(barrySituation how_is_barry)
{
	barryRect = { barryLocation.x, barryLocation.y, 40, 55 };
	if (!gravitySituation)
	{
		switch (how_is_barry)
		{
		case barryWalk:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryWalkPic, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryWalkPic, barryRect);
			break;
		case barryRun:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryRunPic, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryRunPic, barryRect);
			break;
		case barryFly:
			/*if (soundCounter % 100 == 7 && musicFlag)
			{
				SBDL::playSound(jetSound, 1);
				soundCounter++;
			}
			else
				soundCounter++;*/
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryRiseJet, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryRiseJet, barryRect);
			break;
		case barryFall:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryFallPic, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryFallPic, barryRect);
			break;
		}
	}
	else
	{
		switch (how_is_barry)
		{
		case gravityBarryFall:
			SBDL::showTexture(gravityBarryFallPic, barryRect);
			SBDL::playSound(gravityFallSound, 1);
			break;
		case gravityBarryFly:
			SBDL::showTexture(gravityBarryFlyPic, barryRect);
			SBDL::playSound(gravityFlySound, 1);
			break;
		case gravityBarryWalkDown:
			if (walkingCounter % 12 < 6)
			{
				SBDL::showTexture(gravityBarryRunDownPic, barryRect);
				walkingCounter++;
			}
			else if (walkingCounter % 12 >= 6)
			{
				SBDL::showTexture(gravityBarryWalkDownPic, barryRect);
				walkingCounter++;
			}
			break;
		case gravityBarryWalkUp:
			if (walkingCounter % 12 < 6)
			{
				SBDL::showTexture(gravityBarryRunUpPic, barryRect);
				walkingCounter++;
			}
			else if (walkingCounter % 12 >= 6)
			{
				SBDL::showTexture(gravityBarryWalkUpPic, barryRect);
				walkingCounter++;
			}
			break;
		case baryGoFast:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryGoFast, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryGoFast, barryRect);
			break;
		}
	}
	
}
void updateBackGround()
{	
		if (backArray[9].x <= 0)
		{
			finishFlag = true;
			for (int i = 1; i <= 9; i++)
			{
				backArray[0].x = 0;
				backArray[i].x = backArray[0].x + 2048 * i;
			}
		}
		else if (finishFlag)
		{
			for (int i = 1; i <= 9; i++)
			{
				backArray[i].x = backArray[0].x + 2048 * i - 2048;
			}
		}
		else
		{
			finishFlag = false;
			for (int i = 1; i <= 9; i++)
			{
				backArray[i].x = backArray[0].x + 800 + 2048 * (i - 1);
			}
		}
		if (tokenFlag)
		{
			backVelocity = -150;
			notForgetCounter++;
			how_is_barry = baryGoFast;
			backArray[0].x += backVelocity;
			SBDL::showTexture(oldBarryGoFast, barryRect);
			tokenFlag = false;
			backVelocity = -7;
		}
		else if (notForgetCounter == 1)
		{
			barryLocation.x = 380;
			backVelocity = -7;
		}
		backArray[0].x += backVelocity;
}
void drawBackGround(backgroundTypes how_is_back)
{
	if (!finishFlag)
	{
		backRect = { backArray[0].x , 0 , 800 , 460 };
		SBDL::showTexture(backArray[0].pic, backRect);
		for (int i = 1; i <= 9; i++)
		{
			backRect = { backArray[i].x , 0 , 2048 , 460 };
			SBDL::showTexture(backArray[i].pic, backRect);
		}
	}
	else
		for (int i = 1; i <= 9; i++)
		{
			backRect = { backArray[i].x , 0 , 2048 , 460 };
			SBDL::showTexture(backArray[i].pic, backRect);
		}
}
void updateZapper()
{
	//if (!lazerMainFlag)
	{
		if (myZapper.x < -150)
			initZapper();
		myZapper.x += zapperVelocity;

		if (zapperCounter % 24 < 6)
		{
			how_is_zapper = firstZap;
			zapperCounter++;
		}

		else if (zapperCounter % 24 >= 6 && zapperCounter % 24 < 12)
		{
			how_is_zapper = secondZap;
			zapperCounter++;
		}

		else if (zapperCounter % 24 >= 12 && zapperCounter % 24 < 18)
		{
			how_is_zapper = thirdZap;
			zapperCounter++;
		}

		else if (zapperCounter % 24 >= 18)
		{
			how_is_zapper = fourthZap;
			zapperCounter++;
		}

		//drawZapper(how_is_zapper);
	}
}
void drawZapper(zapperShowing how_is_zapper)
{
	//if (!lazerMainFlag)
	{
		switch (how_is_zapper)
		{
		case firstZap:
			switch (which_zapper)
			{
			case 0:
				myZapperRect = { myZapper.x, myZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { myZapper.x, myZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { myZapper.x, myZapper.y, 50, 150 };
			}
			SBDL::showTexture(myZapper.first, myZapperRect);
			break;
		case secondZap:
			switch (which_zapper)
			{
			case 0:
				myZapperRect = { myZapper.x, myZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { myZapper.x, myZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { myZapper.x, myZapper.y, 50, 150 };
			}
			SBDL::showTexture(myZapper.second, myZapperRect);
			break;
		case thirdZap:
			switch (which_zapper)
			{
			case 0:
				myZapperRect = { myZapper.x, myZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { myZapper.x, myZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { myZapper.x, myZapper.y, 50, 150 };
			}
			SBDL::showTexture(myZapper.third, myZapperRect);
			break;
		case fourthZap:
			switch (which_zapper)
			{
			case 0:
				myZapperRect = { myZapper.x, myZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { myZapper.x, myZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { myZapper.x, myZapper.y, 50, 150 };
			}
			SBDL::showTexture(myZapper.fourth, myZapperRect);
			break;
		}
	}
}
void initZapper()
{
	which_zapper = rand() % 3;
	which_zapper_y = rand() % 2 +1;
	myZapper = zappersArray[which_zapper];
	myZapper.y = zapper_y[which_zapper_y];
	myZapper.x = 850 + rand() % 100;
}
void updateMenu()
{
	SBDL::updateEvents();
	menuClickRect = { menuClickCore.x, menuClickCore.y , 60 , 70 };
	homeBarryRect = { barryPoster.x , barryPoster.y , barryPosterSize_x, barryPosterSize_y };
	menuRect = { menuLocation.x, menuLocation.y, window_width, window_height };
	if (menuCounter % 12 < 4)
	{
		how_is_menu = poster1;
		menuCounter++;
	}
	else if (menuCounter % 12 >= 4 && menuCounter % 12 < 8)
	{
		how_is_menu = poster2;
		menuCounter++;
	}
	else if (menuCounter % 12 >= 8)
	{
		how_is_menu = poster3;
		menuCounter++;
	}
	anywhere1 = { 0 , 0, 750, 70 };
	anywhere2 = { 0 , 70, 800, 390 };
	anywhere3 = { 0 , 0 , 510, 70 };
	anywhere4 = { 0 , 70, 560, 390 };
	if (SBDL::mouseInRect(menuClickRect) && SBDL::Mouse.clicked() && menuClickCore.x == 750)
	{
		menuLocation.x = 0;
		barryPoster.x -= 70;
		menuClickCore.x = 510;
		barryPosterSize_x = 400;
		barryPosterSize_y = 200;
		clickAnyWhereFlag = false;
	}
	else if (SBDL::mouseInRect(menuClickRect) && SBDL::Mouse.clicked() && menuClickCore.x == 510)
	{
		menuLocation.x = 240;
		barryPoster.x += 70;
		menuClickCore.x = 750;
		barryPosterSize_x = 600;
		barryPosterSize_y = 300;
		clickAnyWhereFlag = true;
	}
	else if (SBDL::mouseInRect(changeBarryRect) && SBDL::Mouse.clicked() && menuClickCore.x == 510)
	{
		if (oldBarryFlag)
		{
			oldBarryFlag = false;
			youngBarryFlag = true;
		}
		else if (youngBarryFlag)
		{
			youngBarryFlag = false;
			oldBarryFlag = true;
		}
		how_is_menu = changeBarry;
		changeBarryFlag = true;
	}
	else if (SBDL::mouseInRect(quitRect) && SBDL::Mouse.clicked() && menuClickCore.x == 510)
		exit(1);
	else if (SBDL::mouseInRect(oldRect) && SBDL::Mouse.clicked() && how_is_menu == changeBarry)
	{
		changeBarryFlag = false;
		oldBarryFlag = true;
		youngBarryFlag = false;
	}
	else if (SBDL::mouseInRect(youngRect) && SBDL::Mouse.clicked() && how_is_menu == changeBarry)
	{
		changeBarryFlag = false;
		youngBarryFlag = true;
		oldBarryFlag = false;
	}
	else if ((SBDL::mouseInRect(anywhere1) || SBDL::mouseInRect(anywhere2)) && SBDL::Mouse.clicked() && menuClickCore.x == 750 && how_is_menu != changeBarry)
	{
		initializer();
		chum = play;
	}
	else if ((SBDL::mouseInRect(anywhere3) || SBDL::mouseInRect(anywhere4)) && SBDL::Mouse.clicked() && menuClickCore.x == 510 && how_is_menu != changeBarry)
	{
		initializer();
		chum = play;
	}
}
void drawMenu(homeMenu how_is_menu)
{
	switch (how_is_menu)
	{
	case poster1:
		if (changeBarryFlag)
		{
			SBDL::showTexture(darkBlackBack, windowRect);
			SBDL::showTexture(oldBarryRunPic, oldRect);
			SBDL::showTexture(youngBarryRunPic, youngRect);
		}
		else
		{
			SBDL::showTexture(backArray[0].pic, windowRect);
			SBDL::showTexture(blackBack, windowRect);
			SBDL::showTexture(homePageMenu, menuRect);
			SBDL::showTexture(homePic, homeBarryRect);
			if (clickAnyWhereFlag)
				SBDL::showTexture(clickAnyWhere1, clickAnyWhereRect);
		}
		break;
	case poster2:
		if (changeBarryFlag)
		{
			SBDL::showTexture(darkBlackBack, windowRect);
			SBDL::showTexture(oldBarryRunPic, oldRect);
			SBDL::showTexture(youngBarryRunPic, youngRect);
			SBDL::showTexture(chooseText, chooseTextRect);
			SBDL::showTexture(youngText, youngTextRect);
			SBDL::showTexture(oldText, oldTextRect);
		}
		else
		{
			SBDL::showTexture(backArray[0].pic, windowRect);
			SBDL::showTexture(blackBack, windowRect);
			SBDL::showTexture(homePageMenu, menuRect);
			SBDL::showTexture(homePic, homeBarryRect);
			if (clickAnyWhereFlag)
				SBDL::showTexture(clickAnyWhere2, clickAnyWhereRect);
		}
		break;
	case poster3:
		if (changeBarryFlag)
		{
			SBDL::showTexture(darkBlackBack, windowRect);
			SBDL::showTexture(oldBarryRunPic, oldRect);
			SBDL::showTexture(youngBarryRunPic, youngRect);
			SBDL::showTexture(chooseText, chooseTextRect);
			SBDL::showTexture(youngText, youngTextRect);
			SBDL::showTexture(oldText, oldTextRect);
		}
		else
		{
			SBDL::showTexture(backArray[0].pic, windowRect);
			SBDL::showTexture(blackBack, windowRect);
			SBDL::showTexture(homePageMenu, menuRect);
			SBDL::showTexture(homePic2, homeBarryRect);
			if (clickAnyWhereFlag)
				SBDL::showTexture(clickAnyWhere3, clickAnyWhereRect);
		}
		break;
	case changeBarry:
		SBDL::showTexture(darkBlackBack, windowRect);
		SBDL::showTexture(oldBarryRunPic, oldRect);
		SBDL::showTexture(youngBarryRunPic, youngRect);
		SBDL::showTexture(chooseText, chooseTextRect);
		SBDL::showTexture(youngText, youngTextRect);
		SBDL::showTexture(oldText, oldTextRect);
		break;
	}
}
void inFlying()
{
	SBDL::updateEvents();
	if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && barryLocation.y >= 30)
	{
		how_is_barry = barryFly;
		barryLocation.y -= barryVelocity_y;
		if (accelerationCounter % 7 == 0)
		{
			barryVelocity_y += shetab;
			accelerationCounter++;
		}
		else
			accelerationCounter++;
		flyStopFlag = true;
		if (barryLocation.y > 376)
			barryLocation.y = 380;
	}
	else if (barryLocation.y <= 370)
	{
		if (flyStopFlag)
		{
			how_is_barry = barryFall;
			barryVelocity_y = 0;
			if (accelerationCounter % 7 == 0)
			{
				barryVelocity_y += shetab;
				accelerationCounter++;
			}
			else
				accelerationCounter++;
			flyStopFlag = false;
			if (barryLocation.y > 370)
				barryLocation.y = 380;
		}
		else
		{
			how_is_barry = barryFall;
			barryLocation.y += barryVelocity_y;
			if (accelerationCounter % 7 == 0)
			{
				barryVelocity_y += shetab;
				accelerationCounter++;
			}
			else
				accelerationCounter++;
			if (barryLocation.y > 370)
				barryLocation.y = 380;
		}
	}

}
void updateMissle()
{
	if (myMissle.x < -150)
	{
		myMissle.x = 900 + rand() % 150;
	}
	else if (myMissle.x >= 820)
	{
		how_is_missle = missleFar;
		redWarLoc.x = 750;
		redWarLoc.y = barryLocation.y;
		myMissle.y = barryLocation.y;
		myMissle.x -= 10;
	}
	else if (myMissle.x < 830 && myMissle.x > 800)
	{
		how_is_missle = missleNear;
		yellowWarLoc.x = 750;
		yellowWarLoc.y = barryLocation.y;
		myMissle.y = barryLocation.y;
		myMissle.x -= 10;
	}
	else if (myMissle.x <= 800)
	{
		how_is_missle = missleIn;
		myMissle.x -= 10;
	}

}
void drawMissle(missleShowing how_is_missle)
{
	switch (how_is_missle)
	{
	case missleFar:
		warningRect = { 750 , redWarLoc.y , 50 , 50 };
		SBDL::showTexture(redWarning, warningRect);
		break;
	case missleNear:
		warningRect = { yellowWarLoc.x , yellowWarLoc.y , 50 , 50 };
		SBDL::showTexture(yellowWarning, warningRect);
		break;
	case missleIn:
		missleRect = { myMissle.x , myMissle.y , 60 , 60 };
		if (missleCounter % 18 < 3)
		{
			SBDL::showTexture(myMissle.picArray[0], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 3 && missleCounter % 18 < 6)
		{
			SBDL::showTexture(myMissle.picArray[1], missleRect);
			missleCounter++;
		}	
		else if (missleCounter % 18 >= 6 && missleCounter % 18 < 9)
		{
			SBDL::showTexture(myMissle.picArray[2], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 9 && missleCounter % 18 < 12)
		{
			SBDL::showTexture(myMissle.picArray[3], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 12 && missleCounter % 18 < 15 )
		{
			SBDL::showTexture(myMissle.picArray[4], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 15 && missleCounter % 18 < 18)
		{
			SBDL::showTexture(myMissle.picArray[5], missleRect);
			missleCounter++;
		}

		/*missleRect = { randomMissle1.x , randomMissle1.y , 80 , 80 };
		if (missleCounter % 18 < 3)
		{
			SBDL::showTexture(myMissle.picArray[0], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 3 && missleCounter % 18 < 6)
		{
			SBDL::showTexture(myMissle.picArray[1], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 6 && missleCounter % 18 < 9)
		{
			SBDL::showTexture(myMissle.picArray[2], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 9 && missleCounter % 18 < 12)
		{
			SBDL::showTexture(myMissle.picArray[3], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 12 && missleCounter % 18 < 15)
		{
			SBDL::showTexture(myMissle.picArray[4], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 15 && missleCounter % 18 < 18)
		{
			SBDL::showTexture(myMissle.picArray[5], missleRect);
			missleCounter++;
		}
		missleRect = { randomMissle2.x , randomMissle2.y , 80 , 80 };
		if (missleCounter % 18 < 3)
		{
			SBDL::showTexture(myMissle.picArray[0], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 3 && missleCounter % 18 < 6)
		{
			SBDL::showTexture(myMissle.picArray[1], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 6 && missleCounter % 18 < 9)
		{
			SBDL::showTexture(myMissle.picArray[2], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 9 && missleCounter % 18 < 12)
		{
			SBDL::showTexture(myMissle.picArray[3], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 12 && missleCounter % 18 < 15)
		{
			SBDL::showTexture(myMissle.picArray[4], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 15 && missleCounter % 18 < 18)
		{
			SBDL::showTexture(myMissle.picArray[5], missleRect);
			missleCounter++;
		}*/
	}
}
void pausePageFun()
{
	pausePageHomeRect = { 300 , 200, 200, 70 };
	SBDL::showTexture(darkBlackBack, windowRect);
	SBDL::showTexture(retryPic, retryRect);
	SBDL::showTexture(homePicClick, pausePageHomeRect);
	SBDL::showTexture(resumePic, resumeRect);
	SBDL::showTexture(showPaused, showPausedRect);
	SBDL::updateEvents();
	
	if (SBDL::mouseInRect(resumeRect) && SBDL::Mouse.clicked())
	{
		chum = play;
	}

	else if (SBDL::mouseInRect(pausePageHomeRect) && SBDL::Mouse.clicked())
	{
		initializer();
		chum = home;
	}

	else if (SBDL::mouseInRect(retryRect) && SBDL::Mouse.clicked())
	{
		initializer();
		chum = play;
	}
}
void gameOverPageFun()
{
	updateGameOverPage();
	drawGameOverPage();
}
void updateGameOverPage()
{
	SBDL::updateEvents();
	if (SBDL::mouseInRect(gameoverRetryRect) && SBDL::Mouse.clicked())
	{
		initializer();
		chum = play;
	}
	else if (SBDL::mouseInRect(gameoverHomeRect) && SBDL::Mouse.clicked())
	{
		initializer();
		chum = home;
	}
}
void drawGameOverPage()
{
	fontTexture = SBDL::createFontTexture(scoreFont, std::to_string(score/10), 0, 0, 0);
	SBDL::showTexture(darkBlackBack, windowRect);
	SDL_Rect showPosterRect = { 30 , 20 , 350 , 250 };
	if (gameoverCounter % 12 < 6)
	{
		SBDL::showTexture(homePic, showPosterRect);
		gameoverCounter++;
	}
	else
	{
		SBDL::showTexture(homePic2, showPosterRect);
		gameoverCounter++;
	}
	SBDL::showTexture(retryPic, gameoverRetryRect);
	SBDL::showTexture(homePicClick, gameoverHomeRect);
	SDL_Rect scoreRect = { 450 , 50 , 300 , 150 };
	SBDL::showTexture(yourScoreText, scoreRect);
	scoreRect = { 530 , 190 , 150 , 70 };
	SBDL::showTexture(fontTexture, scoreRect);

}
void updateLaser()
{
	if (laserCounter == 0)
	{
		for (int i = 0; i < 5; i++)
			{
				which_lazer_y = rand() % 6;
				mylazer[i].y = lazer_y[which_lazer_y];
				mylazer[i].existance = rand() % 2;
			}
		laserCounter++;
	}
	else
	{
		if (laserCounter % 100 < 50)
		{
			how_is_laser = nonactive;
			laserCounter++;
		}
		else if (laserCounter % 100 >= 50 && laserCounter % 50 < 75)
		{
			how_is_laser = active1;
			laserCounter++;
		}
		else if (laserCounter % 100 >= 75 && laserCounter % 100 < 100)
		{
			how_is_laser = active2;
			laserCounter++;
		}
	}
}
void drawLaser(laserShowing how_is_laser)
{
	switch (how_is_laser)
	{
	case nonactive:
		for (int i = 0; i < 5; i++)
		{
			mylazer[i].Rect = { 30 , mylazer[i].y , 740 , 50 };
			if (mylazer[i].existance = 1)
				SBDL::showTexture(mylazer[i].nonactive, myLazerRect);
		}	
		break;
	case active1:
		for (int i = 0; i < 5; i++)
		{
			myLazerRect = { 30 , mylazer[i].y , 740 , 50 };
			if (mylazer[i].existance = 1)
				SBDL::showTexture(mylazer[i].active1, myLazerRect);
		}
		break;
	case active2:
		for (int i = 0; i < 5; i++)
		{
			myLazerRect = { 30 , mylazer[i].y , 740 , 50 };
			if (mylazer[i].existance = 1)
				SBDL::showTexture(mylazer[i].active2, myLazerRect);
		}
		break;
	}
}
void updateSpeedToken()
{
	myTokenRect = { myToken.x , tempToken_y , 60 , 60 };
	if (myToken.x < -150)
	{ 
		//while (myToken.x - myZapper.x < 50 || myToken.x - myZapper.x > -50)
			myToken.x = 830 + rand() % 100;
		//while (myToken.y - myZapper.y < 50 || myToken.y - myZapper.y > -50)
			myToken.y = 50 + rand() % 350;
		tempToken_y = myToken.y;
	}
	myToken.x += backVelocity;
}
void drawSpeedToken()
{
	if (!tokenFlag)
	{
		if (tokenCounter % 24 < 6)
		{
			SBDL::showTexture(myToken.pic1, myTokenRect);
			tokenCounter++;
		}
		if (tokenCounter % 24 >= 6 && tokenCounter % 24 < 12)
		{
			SBDL::showTexture(myToken.pic2, myTokenRect);
			tokenCounter++;
		}
		if (tokenCounter % 24 >= 12 && tokenCounter % 24 < 18)
		{
			SBDL::showTexture(myToken.pic3, myTokenRect);
			tokenCounter++;
		}
		if (tokenCounter % 24 >= 18 && tokenCounter % 24 < 24)
		{
			SBDL::showTexture(myToken.pic4, myTokenRect);
			tokenCounter++;
		}
	}
	else
	{
		/*for (int i = 0; i < 100; i++)
		{
			SBDL::clearRenderScreen();
			int tokenStartTime = SBDL::getTime();
			updateBackGround();
			drawBackGround(how_is_back);
			SBDL::showTexture(oldBarryGoFast, barryRect);
			int tokenElapsedTime = SBDL::getTime() - startTime;
			if (elapsedTime < delay)
				SBDL::delay(delay - tokenElapsedTime);
			SBDL::updateRenderScreen();
		}*/
	}
}
void updateGravityToken()
{
	if (gToken.x < -150)
	{
		gToken.x = 850 + rand() % 100;
		gToken.y = 30 + rand() % 350;
		
	}
	gToken.x += backVelocity;
}
void drawGravityToken()
{
	GTokenRect = { gToken.x , gToken.y , 50 , 50 };
	if (GtokenConter % 44 < 4)
	{
		SBDL::showTexture(gravityToken, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 4 && GtokenConter % 44 < 8)
	{
		SBDL::showTexture(gravityToken1, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 8 && GtokenConter % 44 < 12)
	{
		SBDL::showTexture(gravityToken2, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 12 && GtokenConter % 44 < 16)
	{
		SBDL::showTexture(gravityToken3, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 16 && GtokenConter % 44 < 20)
	{
		SBDL::showTexture(gravityToken4, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 20 && GtokenConter % 44 < 24)
	{
		SBDL::showTexture(gravityToken5, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 24 && GtokenConter % 44 < 28)
	{
		SBDL::showTexture(gravityToken6, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 28 && GtokenConter % 44 < 32)
	{
		SBDL::showTexture(gravityToken7, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 32 && GtokenConter % 44 < 36)
	{
		SBDL::showTexture(gravityToken8, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 36 && GtokenConter % 44 < 40)
	{
		SBDL::showTexture(gravityToken9, GTokenRect);
		GtokenConter++;
	}
	else if (GtokenConter % 44 >= 40 && GtokenConter % 44 < 44)
	{
		SBDL::showTexture(gravityToken10, GTokenRect);
		GtokenConter++;
	}
}
void gravityFlyFall()
{
	gravitySituation = true;
	SBDL::updateEvents();
	if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && barryLocation.y <= 380 && barryLocation.y != 30)
	{
		gravitySituation = true;
		how_is_barry = gravityBarryFly;
		barryLocation.y -= barryVelocity_y;
		if (barryLocation.y < 50)
		{
			barryLocation.y = 30;
			how_is_barry = gravityBarryWalkUp;
		}
	}
	SBDL::updateEvents();
	if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && barryLocation.y >= 30 && barryLocation.y != 380)
	{
		how_is_barry = gravityBarryFall;
		barryLocation.y += barryVelocity_y;
		if (barryLocation.y > 360)
		{
			barryLocation.y = 380;
			how_is_barry = gravityBarryWalkDown;
		}
	}
}
void zapperFun()
{
	if (myZapper.x < -120 && myZapper.x > -150)
	{
		zapperMainFlag = false;
		myZapper.x = -200;
		happenings();
	}
	if (zapperMainFlag)
	{
		updateZapper();
		drawZapper(how_is_zapper);
	}
}
void missleFun()
{
	if (myMissle.x < -100 && myMissle.x > -150)
	{
		missleMainFlag = false;
		myMissle.x = -200;
		happenings();
	}
	if (missleMainFlag)
	{
		updateMissle();
		drawMissle(how_is_missle);
	}
}
void lazerFun()
{
	if (lazerMainFlag)
	{
		updateLaser();
		drawLaser(how_is_laser);
	}
	if (laserCounter == 99)
	{
		lazerMainFlag = false;
		laserCounter = 0;
		happenings();
	}
		
}
void gravityFun()
{
	if (gToken.x < -100 && gToken.x > -150)
	{
		gravityTokenMainFlag = false;
		gToken.x = -200;
		happenings();
	}
	if (gravityTokenMainFlag)
	{
		updateGravityToken();
		drawGravityToken();
	}
}
void speedFun()
{
	if (myToken.x < -100 && myToken.x > -150)
	{
		speedTokenMainFlag = false;
		myToken.x = -200;
		happenings();
	}
	if (speedTokenMainFlag)
	{
		updateSpeedToken();
		drawSpeedToken();
	}
}