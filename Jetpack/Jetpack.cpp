#include "stdafx.h"
#include "SBDL.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

enum GameState {
    STATE_START,
    STATE_PLAY,
    STATE_HOME,
    STATE_PAUSE,
    STATE_GAME_OVER,
    STATE_COIN_EVENT,
    STATE_LASER_EVENT,
    STATE_MISSILE_EVENT,
    STATE_SPEED_TOKEN_EVENT,
    STATE_ZAPPER_EVENT,
    STATE_GRAVITY_TOKEN_EVENT
};

enum BarrySituation {
    BARRY_RUN,
    BARRY_WALK,
    BARRY_FLY,
    BARRY_FALL,
    BARRY_GRAVITY_FLY,
    BARRY_GRAVITY_FALL,
    BARRY_GRAVITY_WALK_DOWN,
    BARRY_GRAVITY_WALK_UP,
    BARRY_GRAVITY_RUN_DOWN,
    BARRY_GRAVITY_RUN_UP,
    BARRY_GO_FAST
};

enum BackgroundType {
    BACKGROUND_FIRST,
    BACKGROUND_OTHER,
    BACKGROUND_WARE
};

enum ZapperState {
    ZAPPER_FIRST,
    ZAPPER_SECOND,
    ZAPPER_THIRD,
    ZAPPER_FOURTH
};

enum HomeMenuState {
    HOME_POSTER1,
    HOME_POSTER2,
    HOME_POSTER3,
    HOME_CHANGE_BARRY
};

enum MissileState {
	MISSILE_FAR, 
	MISSILE_NEAR, 
	MISSILE_IN
};

enum LaserState {
	LASER_NONACTIVE, 
	LASER_ACTIVE1, 
	LASER_ACTIVE2
};

struct Core {
	int x;
	int y;
};

struct Zapper {
	Texture first;
	Texture second;
	Texture third;
	Texture fourth;
	int x;
	int y;
};

struct Laser {
	Texture nonactive;
	Texture active1;
	Texture active2;
	int existance;
	int x;
	int y;
	SDL_Rect rect;
};

struct Background {
	Texture pic;
	int x;
};

struct Missle {
	Texture picArray[6];
	int x;
	int y;
};

struct SpeedToken {
	Texture pic1;
	Texture pic2;
	Texture pic3;
	Texture pic4;
	int x;
	int y;
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 460;
const int FPS = 60; //frame per second
const int DELAY = 1000 / FPS; //delay we need at each frame

GameState currentGameState;

Core playerLocation;
Core backgroundLocation;
Core redWarriorLocation;
Core yellowWarriorLocation;
Core randomRedWarriorLocation1;
Core randomYellowWarriorLocation1;
Core randomRedWarriorLocation2;
Core randomYellowWarriorLocation2;
Core barryPoster;
Core menuClickCore;
Core menuLocation;
Core gravityTokenCore;

Zapper obstacleZapper;
SpeedToken obstacleToken;
BackgroundType currentBackgroundType;
ZapperState currentZapperState;
HomeMenuState currentHomeMenuState;
MissileState currentMissileState;
LaserState currentLaserState;
BarrySituation currentBarrySituation;

Laser playerLaser[6];
Missle playerMissle;
Missle randomMissle1;
Missle randomMissle2;
Zapper horizentalZap;
Zapper verticalZap;
Zapper angledZap;
Zapper zappersArray[3];
GameState eventsArray[6] = { STATE_MISSILE_EVENT , STATE_GRAVITY_TOKEN_EVENT , 
							STATE_MISSILE_EVENT , STATE_SPEED_TOKEN_EVENT , 
							STATE_MISSILE_EVENT ,STATE_LASER_EVENT };


int zapperY[3] = { 35 , 150 , 280 };
int currentZapperX;
int currentZapperY;
int currentZapper;

int barryVelocityY;


int backVelocity = -7;
int zapperVelocity = -7;

int currentBackground;
int acceleration;

int walkingCounter;
int zapperCounter;
int menuCounter;
int missleCounter;
int gameoverCounter;
int laserCounter;
int tokenCounter;
int GtokenConter;
int accelerationCounter;
int soundCounter;
int notForgetCounter;

int barryPosterSizeX;
int barryPosterSizeY;

int tempTokenY;
int laserY[6] = { 30, 105 , 180 , 255 , 330 , 405 };
int currentLaserY;
int elapsedTime, startTime;
int randomEvents;

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
SDL_Rect barryRect = { playerLocation.x, playerLocation.y, 25, 32 };
SDL_Rect windowRect = { 0 , 0, WINDOW_WIDTH, WINDOW_HEIGHT };
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

Background backArray[12];
Background startPage;
Background labStart;
Background lab1;
Background lab2;
Background sectorStart;
Background sector1;
Background sector2;
Background volcanoStart;
Background volcano1;
Background volcano2;
Background warehouseStart;
Background warehouse;

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

void executeState();
void executeGameLogic();
void initializeGameVariables();
void triggerRandomEvent();
void updateBarry();
void drawBarry();
void updateBackground();
void drawBackground();
void updateZapper();
void drawZapper();
void initZapper();
void updateMenu();
void drawMenu(HomeMenuState);
void handleFlyingMovement();
void updateMissle();
void drawMissle(MissileState);
void renderGameScreen();
void displayPausePage();
void handleGameOverPage();
void updateGameOverPage();
void drawGameOverPage();
void updateLaser();
void drawLaser(LaserState);
void updateSpeedToken();
void drawSpeedToken();
void updateGravityToken();
void drawGravityToken();
void handleGravityFlyFall();
void handleZapper();
void handleMissile();
void handleLaser();
void handleGravityToken();
void handleSpeedToken();
void loadAssets();

int main()
{
	srand(time(NULL));
	SBDL::InitEngine("Jetpack_Joyride", WINDOW_WIDTH, WINDOW_HEIGHT);

	
	loadAssets();
	initializeGameVariables();
	triggerRandomEvent();
	SBDL::playMusic(gameMusic, -1);
	while (SBDL::isRunning())
	{
		startTime = SBDL::getTime();
		SBDL::clearRenderScreen();

		executeState();

		SBDL::updateRenderScreen();
		elapsedTime = SBDL::getTime() - startTime;
		if (elapsedTime < DELAY)
			SBDL::delay(DELAY - elapsedTime);
	}
}

void loadAssets() 
{
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
		playerLaser[i].nonactive = SBDL::loadTexture("assets/pic/lazer/laser_noneactive.png");
		playerLaser[i].active1 = SBDL::loadTexture("assets/pic/lazer/laser_active1.png");
		playerLaser[i].active2 = SBDL::loadTexture("assets/pic/lazer/laser_active2.png");
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
	clickAnyWhere2 = SBDL::loadTexture("assets/pic/menu/clickanywhere.png", 100);
	clickAnyWhere3 = SBDL::loadTexture("assets/pic/menu/clickanywhere.png", 50);
	playerMissle.picArray[0] = SBDL::loadTexture("assets/pic/missle/missle (1).png");
	playerMissle.picArray[1] = SBDL::loadTexture("assets/pic/missle/missle (2).png");
	playerMissle.picArray[2] = SBDL::loadTexture("assets/pic/missle/missle (3).png");
	playerMissle.picArray[3] = SBDL::loadTexture("assets/pic/missle/missle (4).png");
	playerMissle.picArray[4] = SBDL::loadTexture("assets/pic/missle/missle (5).png");
	playerMissle.picArray[5] = SBDL::loadTexture("assets/pic/missle/missle (6).png");
	redWarning = SBDL::loadTexture("assets/pic/missle/1m.png");
	yellowWarning = SBDL::loadTexture("assets/pic/missle/2m.png");
	oldText = SBDL::loadTexture("assets/pic/menu/old text.png");
	youngText = SBDL::loadTexture("assets/pic/menu/young text.png");
	chooseText = SBDL::loadTexture("assets/pic/menu/choose barry.png");
	homePicClick = SBDL::loadTexture("assets/pic/menu/home.png.");
	obstacleToken.pic1 = SBDL::loadTexture("assets/pic/speedToken/speed token.png");
	obstacleToken.pic2 = SBDL::loadTexture("assets/pic/speedToken/speed token2.png");
	obstacleToken.pic3 = SBDL::loadTexture("assets/pic/speedToken/speed token3.png");
	obstacleToken.pic4 = SBDL::loadTexture("assets/pic/speedToken/speed token4.png");
	zapperSound = SBDL::loadSound("assets/sound/zapper.wav");
	missleWarninSound = SBDL::loadSound("assets/sound/missile_warning.wav");
	missleLounchSound = SBDL::loadSound("assets/sound/missile_launch.wav");
	gravityFlySound = SBDL::loadSound("assets/sound/grav_change_1.wav");
	gravityFallSound = SBDL::loadSound("assets/sound/grav_change_2.wav");
	jetSound = SBDL::loadSound("assets/sound/jetpack_se.wav");
	yourScoreText = SBDL::loadTexture("assets/pic/menu/your score.png");
	gameMusic = SBDL::loadMusic("assets/sound/my_music.wav");
	showPaused = SBDL::loadTexture("assets/pic/menu/paused.png");
	scoreFont = SBDL::loadFont("assets/font/Jetpackia.ttf", 60);

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
}

/*Renders the game screen by updating and drawing various
game elements such as the background, player character, 
zappers, animations, and the pause button.*/
void renderGameScreen()
{
	SBDL::clearRenderScreen();
	SBDL::updateEvents();
	updateBackground();
	updateBarry();
	updateZapper();
	drawBackground();

	drawZapper();
	handleZapper();
	handleMissile();
	handleLaser();
	handleGravityToken();
	handleSpeedToken();
	drawBarry();
	SBDL::showTexture(pausePic, pauseRect);
	SBDL::updateRenderScreen();
}

/*Executes the logic for the current game state, which 
includes actions such as updating the menu, drawing the menu, 
handling pause functionality, or displaying the game over screen.*/
void executeState()
{
	switch (currentGameState)
	{
	case STATE_PLAY:
		executeGameLogic();
		break;
	case STATE_HOME:
		updateMenu();
		drawMenu(currentHomeMenuState);
		break;
	case STATE_PAUSE:
		displayPausePage();
		break;
	case STATE_GAME_OVER:
		handleGameOverPage();
		break;
	}
}

/*Initializes various game variables and flags to their default values
 at the start of the game. Sets the initial values for flags related 
 to gameplay states, sound settings, and character selection. 
 Resets the current game state, counters, score, player location, 
 velocity, and other relevant variables to their initial states.*/
void initializeGameVariables()
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

	currentGameState = STATE_HOME;

	walkingCounter = 0;
	zapperCounter = 0;

	score = 0;

	playerLocation.x = 0;
	playerLocation.y = 380;
	barryVelocityY = 1;

	for (int i = 0; i < 11; i++)
	{
		if (i == 0)
			backArray[i].x = 0;
		else
			backArray[i].x = 800 + 2048 * (i - 1);
	}

	acceleration = 1;

	barryPoster.x = 100;
	barryPoster.y = 50;
	barryPosterSizeX = 600;
	barryPosterSizeY = 300;
	menuClickCore.x = 750;
	menuClickCore.y = 0;
	menuCounter = 0;
	menuLocation.x = 240;
	menuLocation.y = 0;

	obstacleZapper.x = -200;
	playerMissle.x = -200;
	obstacleToken.x = -200;
	gravityTokenCore.x = -200;

	barryRect = { playerLocation.x, playerLocation.y, 50, 70 };
}

/*Triggers a random event in the game. Generates a random number 
to select an event from the eventsArray. Depending on the selected 
event, sets the corresponding flags and initializes any 
relevant variables. Events can include laser activation, 
missile activation, speed token appearance, or gravity token appearance.*/
void triggerRandomEvent()
{
	randomEvents = rand() % 6;
	switch (eventsArray[randomEvents])
	{
	case STATE_LASER_EVENT:
		lazerMainFlag = true;
		//newLaserFlag = true;
		laserCounter = 0;
		break;
	case STATE_MISSILE_EVENT:
		missleMainFlag = true;
		break;
		/*case zapperEvent:
		zapperMainFlag = true;
		break;*/
	case STATE_SPEED_TOKEN_EVENT:
		speedTokenMainFlag = true;
		break;
	case STATE_GRAVITY_TOKEN_EVENT:
		gravityTokenMainFlag = true;
		break;
	}
}

/* Executes the main game logic. Updates the game display, 
increases the score, and checks for various collision 
conditions to update the game state.*/
void executeGameLogic()
{
	renderGameScreen();
	score++;
	if (SBDL::mouseInRect(pauseRect))
		currentGameState = STATE_PAUSE;
	if (SBDL::hasIntersectionRect(barryRect, missleRect) && gravitySituation == false)
		currentGameState = STATE_GAME_OVER;
	if (SBDL::hasIntersectionRect(barryRect, myZapperRect) && gravitySituation == false)
	{
		if (currentZapper == 1 || currentZapper == 2)
			currentGameState = STATE_GAME_OVER;
		else
		{
			SDL_Rect angledZapper1 = { obstacleZapper.x + 80 , obstacleZapper.y , 40 , 40 };
			SDL_Rect angledZapper2 = { obstacleZapper.x + 40 , obstacleZapper.y + 40 , 40 , 40 };
			SDL_Rect angledZapper3 = { obstacleZapper.x , obstacleZapper.y + 80 , 40 , 40 };
			if (SBDL::hasIntersectionRect(barryRect, angledZapper1) || SBDL::hasIntersectionRect(barryRect, angledZapper2) || SBDL::hasIntersectionRect(barryRect, angledZapper3))
				currentGameState = STATE_GAME_OVER;
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
		playerLocation.y = 380;
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
	currentBarrySituation = BARRY_GO_FAST;
}


// BARRY
void updateBarry()
{
	SBDL::updateEvents();
	if (!gravitySituation)
	{
		if (playerLocation.x < 110)
		{
			playerLocation.x += 1;

			if (walkingCounter % 12 < 6 && playerLocation.y >= 380)
			{
				currentBarrySituation = BARRY_WALK;
				walkingCounter++;
			}
			else if (walkingCounter % 12 >= 6 && playerLocation.y >= 380)
			{
				currentBarrySituation = BARRY_RUN;
				walkingCounter++;
				handleFlyingMovement();
			}
			handleFlyingMovement();
		}
		if (walkingCounter % 12 < 6 && playerLocation.y >= 380)
		{
			currentBarrySituation = BARRY_WALK;
			walkingCounter++;
		}
		else if (walkingCounter % 12 >= 6 && playerLocation.y >= 380)
		{
			currentBarrySituation = BARRY_RUN;
			walkingCounter++;
		}
		handleFlyingMovement();
	}
	else
	{
		handleGravityFlyFall();
	}
}

void drawBarry()
{
	barryRect = { playerLocation.x, playerLocation.y, 40, 55 };
	if (!gravitySituation)
	{
		switch (currentBarrySituation)
		{
		case BARRY_WALK:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryWalkPic, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryWalkPic, barryRect);
			break;
		case BARRY_RUN:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryRunPic, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryRunPic, barryRect);
			break;
		case BARRY_FLY:
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
		case BARRY_FALL:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryFallPic, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryFallPic, barryRect);
			break;
		}
	}
	else
	{
		switch (currentBarrySituation)
		{
		case BARRY_GRAVITY_FALL:
			SBDL::showTexture(gravityBarryFallPic, barryRect);
			SBDL::playSound(gravityFallSound, 1);
			break;
		case BARRY_GRAVITY_FLY:
			SBDL::showTexture(gravityBarryFlyPic, barryRect);
			SBDL::playSound(gravityFlySound, 1);
			break;
		case BARRY_GRAVITY_WALK_DOWN:
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
		case BARRY_GRAVITY_WALK_UP:
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
		case BARRY_GO_FAST:
			if (oldBarryFlag)
				SBDL::showTexture(oldBarryGoFast, barryRect);
			else if (youngBarryFlag)
				SBDL::showTexture(youngBarryGoFast, barryRect);
			break;
		}
	}

}

/*Manages the player's movement during the flying state. 
It handles upward movement when the space key is held, 
increasing the velocity and clamping the maximum height. 
If the player is below a certain height, it handles the 
transition from flying to falling, controlling 
the velocity and clamping the minimum height.*/
void handleFlyingMovement()
{
	SBDL::updateEvents();
	if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && playerLocation.y >= 30)
	{
		currentBarrySituation = BARRY_FLY;
		playerLocation.y -= barryVelocityY;
		if (accelerationCounter % 7 == 0)
		{
			barryVelocityY += acceleration;
			accelerationCounter++;
		}
		else
			accelerationCounter++;
		flyStopFlag = true;
		if (playerLocation.y > 376)
			playerLocation.y = 380;
	}
	else if (playerLocation.y <= 370)
	{
		if (flyStopFlag)
		{
			currentBarrySituation = BARRY_FALL;
			barryVelocityY = 0;
			if (accelerationCounter % 7 == 0)
			{
				barryVelocityY += acceleration;
				accelerationCounter++;
			}
			else
				accelerationCounter++;
			flyStopFlag = false;
			if (playerLocation.y > 370)
				playerLocation.y = 380;
		}
		else
		{
			currentBarrySituation = BARRY_FALL;
			playerLocation.y += barryVelocityY;
			if (accelerationCounter % 7 == 0)
			{
				barryVelocityY += acceleration;
				accelerationCounter++;
			}
			else
				accelerationCounter++;
			if (playerLocation.y > 370)
				playerLocation.y = 380;
		}
	}

}


/*Updates the gravity situation and handles the player character's
vertical movement based on the gravity state. The player moves up 
(gravityFly) or down (gravityFall) when the space key is held, 
within specific bounds. Adjusts the player's position and updates 
the current situation (gravityWalkUp or gravityWalkDown) when the
upper or lower limit is reached.*/
void handleGravityFlyFall()
{
	gravitySituation = true;
	SBDL::updateEvents();
	if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && playerLocation.y <= 380 && playerLocation.y != 30)
	{
		gravitySituation = true;
		currentBarrySituation = BARRY_GRAVITY_FLY;
		playerLocation.y -= barryVelocityY;
		if (playerLocation.y < 50)
		{
			playerLocation.y = 30;
			currentBarrySituation = BARRY_GRAVITY_WALK_UP;
		}
	}
	SBDL::updateEvents();
	if (SBDL::keyHeld(SDL_SCANCODE_SPACE) && playerLocation.y >= 30 && playerLocation.y != 380)
	{
		currentBarrySituation = BARRY_GRAVITY_FALL;
		playerLocation.y += barryVelocityY;
		if (playerLocation.y > 360)
		{
			playerLocation.y = 380;
			currentBarrySituation = BARRY_GRAVITY_WALK_DOWN;
		}
	}
}


// BACKGROUND
void updateBackground()
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
		currentBarrySituation = BARRY_GO_FAST;
		backArray[0].x += backVelocity;
		SBDL::showTexture(oldBarryGoFast, barryRect);
		tokenFlag = false;
		backVelocity = -7;
	}
	else if (notForgetCounter == 1)
	{
		playerLocation.x = 380;
		backVelocity = -7;
	}
	backArray[0].x += backVelocity;
}

void drawBackground()
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


// ZAPPER
void initZapper()
{
	currentZapper = rand() % 3;
	currentZapperY = rand() % 2 + 1;
	obstacleZapper = zappersArray[currentZapper];
	obstacleZapper.y = zapperY[currentZapperY];
	obstacleZapper.x = 850 + rand() % 100;
}

void updateZapper()
{
	//if (!lazerMainFlag)
	{
		if (obstacleZapper.x < -150)
			initZapper();
		obstacleZapper.x += zapperVelocity;

		if (zapperCounter % 24 < 6)
		{
			currentZapperState = ZAPPER_FIRST;
			zapperCounter++;
		}

		else if (zapperCounter % 24 >= 6 && zapperCounter % 24 < 12)
		{
			currentZapperState = ZAPPER_SECOND;
			zapperCounter++;
		}

		else if (zapperCounter % 24 >= 12 && zapperCounter % 24 < 18)
		{
			currentZapperState = ZAPPER_THIRD;
			zapperCounter++;
		}

		else if (zapperCounter % 24 >= 18)
		{
			currentZapperState = ZAPPER_FOURTH;
			zapperCounter++;
		}

		//drawZapper(how_is_zapper);
	}
}

void drawZapper()
{
	//if (!lazerMainFlag)
	{
		switch (currentZapperState)
		{
		case ZAPPER_FIRST:
			switch (currentZapper)
			{
			case 0:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 50, 150 };
			}
			SBDL::showTexture(obstacleZapper.first, myZapperRect);
			break;
		case ZAPPER_SECOND:
			switch (currentZapper)
			{
			case 0:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 50, 150 };
			}
			SBDL::showTexture(obstacleZapper.second, myZapperRect);
			break;
		case ZAPPER_THIRD:
			switch (currentZapper)
			{
			case 0:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 50, 150 };
			}
			SBDL::showTexture(obstacleZapper.third, myZapperRect);
			break;
		case ZAPPER_FOURTH:
			switch (currentZapper)
			{
			case 0:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 120, 120 };
				break;
			case 1:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 150, 50 };
				break;
			case 2:
				myZapperRect = { obstacleZapper.x, obstacleZapper.y, 50, 150 };
			}
			SBDL::showTexture(obstacleZapper.fourth, myZapperRect);
			break;
		}
	}
}

/*Manages the zapper functionality. Resets and triggers 
a random event when the zapper reaches a specific position. 
Updates and draws the zapper when the zapperMainFlag is true.*/
void handleZapper()
{
	if (obstacleZapper.x < -120 && obstacleZapper.x > -150)
	{
		zapperMainFlag = false;
		obstacleZapper.x = -200;
		triggerRandomEvent();
	}
	if (zapperMainFlag)
	{
		updateZapper();
		drawZapper();
	}
}


// MENU
void updateMenu()
{
	SBDL::updateEvents();
	menuClickRect = { menuClickCore.x, menuClickCore.y , 60 , 70 };
	homeBarryRect = { barryPoster.x , barryPoster.y , barryPosterSizeX, barryPosterSizeY };
	menuRect = { menuLocation.x, menuLocation.y, WINDOW_WIDTH, WINDOW_HEIGHT };
	if (menuCounter % 12 < 4)
	{
		currentHomeMenuState = HOME_POSTER1;
		menuCounter++;
	}
	else if (menuCounter % 12 >= 4 && menuCounter % 12 < 8)
	{
		currentHomeMenuState = HOME_POSTER2;
		menuCounter++;
	}
	else if (menuCounter % 12 >= 8)
	{
		currentHomeMenuState = HOME_POSTER3;
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
		barryPosterSizeX = 400;
		barryPosterSizeY = 200;
		clickAnyWhereFlag = false;
	}
	else if (SBDL::mouseInRect(menuClickRect) && SBDL::Mouse.clicked() && menuClickCore.x == 510)
	{
		menuLocation.x = 240;
		barryPoster.x += 70;
		menuClickCore.x = 750;
		barryPosterSizeX = 600;
		barryPosterSizeY = 300;
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
		currentHomeMenuState = HOME_CHANGE_BARRY;
		changeBarryFlag = true;
	}
	else if (SBDL::mouseInRect(quitRect) && SBDL::Mouse.clicked() && menuClickCore.x == 510)
		exit(1);
	else if (SBDL::mouseInRect(oldRect) && SBDL::Mouse.clicked() && currentHomeMenuState == HOME_CHANGE_BARRY)
	{
		changeBarryFlag = false;
		oldBarryFlag = true;
		youngBarryFlag = false;
	}
	else if (SBDL::mouseInRect(youngRect) && SBDL::Mouse.clicked() && currentHomeMenuState == HOME_CHANGE_BARRY)
	{
		changeBarryFlag = false;
		youngBarryFlag = true;
		oldBarryFlag = false;
	}
	else if ((SBDL::mouseInRect(anywhere1) || SBDL::mouseInRect(anywhere2)) && SBDL::Mouse.clicked() && menuClickCore.x == 750 && currentHomeMenuState != HOME_CHANGE_BARRY)
	{
		initializeGameVariables();
		currentGameState = STATE_PLAY;
	}
	else if ((SBDL::mouseInRect(anywhere3) || SBDL::mouseInRect(anywhere4)) && SBDL::Mouse.clicked() && menuClickCore.x == 510 && currentHomeMenuState != HOME_CHANGE_BARRY)
	{
		initializeGameVariables();
		currentGameState = STATE_PLAY;
	}
}

void drawMenu(HomeMenuState currentHomeMenuState)
{
	switch (currentHomeMenuState)
	{
	case HOME_POSTER1:
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
	case HOME_POSTER2:
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
	case HOME_POSTER3:
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
	case HOME_CHANGE_BARRY:
		SBDL::showTexture(darkBlackBack, windowRect);
		SBDL::showTexture(oldBarryRunPic, oldRect);
		SBDL::showTexture(youngBarryRunPic, youngRect);
		SBDL::showTexture(chooseText, chooseTextRect);
		SBDL::showTexture(youngText, youngTextRect);
		SBDL::showTexture(oldText, oldTextRect);
		break;
	}
}


// MISSLE
void updateMissle()
{
	if (playerMissle.x < -150)
	{
		playerMissle.x = 900 + rand() % 150;
	}
	else if (playerMissle.x >= 820)
	{
		currentMissileState = MISSILE_FAR;
		redWarriorLocation.x = 750;
		redWarriorLocation.y = playerLocation.y;
		playerMissle.y = playerLocation.y;
		playerMissle.x -= 10;
	}
	else if (playerMissle.x < 830 && playerMissle.x > 800)
	{
		currentMissileState = MISSILE_NEAR;
		yellowWarriorLocation.x = 750;
		yellowWarriorLocation.y = playerLocation.y;
		playerMissle.y = playerLocation.y;
		playerMissle.x -= 10;
	}
	else if (playerMissle.x <= 800)
	{
		currentMissileState = MISSILE_IN;
		playerMissle.x -= 10;
	}

}

void drawMissle(MissileState currentMissileState)
{
	switch (currentMissileState)
	{
	case MISSILE_FAR:
		warningRect = { 750 , redWarriorLocation.y , 50 , 50 };
		SBDL::showTexture(redWarning, warningRect);
		break;
	case MISSILE_NEAR:
		warningRect = { yellowWarriorLocation.x , yellowWarriorLocation.y , 50 , 50 };
		SBDL::showTexture(yellowWarning, warningRect);
		break;
	case MISSILE_IN:
		missleRect = { playerMissle.x , playerMissle.y , 60 , 60 };
		if (missleCounter % 18 < 3)
		{
			SBDL::showTexture(playerMissle.picArray[0], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 3 && missleCounter % 18 < 6)
		{
			SBDL::showTexture(playerMissle.picArray[1], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 6 && missleCounter % 18 < 9)
		{
			SBDL::showTexture(playerMissle.picArray[2], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 9 && missleCounter % 18 < 12)
		{
			SBDL::showTexture(playerMissle.picArray[3], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 12 && missleCounter % 18 < 15)
		{
			SBDL::showTexture(playerMissle.picArray[4], missleRect);
			missleCounter++;
		}
		else if (missleCounter % 18 >= 15 && missleCounter % 18 < 18)
		{
			SBDL::showTexture(playerMissle.picArray[5], missleRect);
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

/*Manages the missile functionality. Resets and triggers 
a random event when the missile reaches a specific position. 
Updates and draws the missile when the missleMainFlag is true.*/
void handleMissile()
{
	if (playerMissle.x < -100 && playerMissle.x > -150)
	{
		missleMainFlag = false;
		playerMissle.x = -200;
		triggerRandomEvent();
	}
	if (missleMainFlag)
	{
		updateMissle();
		drawMissle(currentMissileState);
	}
}


// LASER
void updateLaser()
{
	if (laserCounter == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			currentLaserY = rand() % 6;
			playerLaser[i].y = laserY[currentLaserY];
			playerLaser[i].existance = rand() % 2;
		}
		laserCounter++;
	}
	else
	{
		if (laserCounter % 100 < 50)
		{
			currentLaserState = LASER_NONACTIVE;
			laserCounter++;
		}
		else if (laserCounter % 100 >= 50 && laserCounter % 50 < 75)
		{
			currentLaserState = LASER_ACTIVE1;
			laserCounter++;
		}
		else if (laserCounter % 100 >= 75 && laserCounter % 100 < 100)
		{
			currentLaserState = LASER_ACTIVE2;
			laserCounter++;
		}
	}
}

void drawLaser(LaserState currentLaserState)
{
	switch (currentLaserState)
	{
	case LASER_NONACTIVE:
		for (int i = 0; i < 5; i++)
		{
			playerLaser[i].rect = { 30 , playerLaser[i].y , 740 , 50 };
			if (playerLaser[i].existance = 1)
				SBDL::showTexture(playerLaser[i].nonactive, myLazerRect);
		}
		break;
	case LASER_ACTIVE1:
		for (int i = 0; i < 5; i++)
		{
			myLazerRect = { 30 , playerLaser[i].y , 740 , 50 };
			if (playerLaser[i].existance = 1)
				SBDL::showTexture(playerLaser[i].active1, myLazerRect);
		}
		break;
	case LASER_ACTIVE2:
		for (int i = 0; i < 5; i++)
		{
			myLazerRect = { 30 , playerLaser[i].y , 740 , 50 };
			if (playerLaser[i].existance = 1)
				SBDL::showTexture(playerLaser[i].active2, myLazerRect);
		}
		break;
	}
}

/*Manages the laser functionality. If lazerMainFlag is true, 
it updates and draws the laser. If the laserCounter reaches 99, 
the lazerMainFlag is set to false, the laserCounter is reset, 
and a random event is triggered.*/
void handleLaser()
{
	if (lazerMainFlag)
	{
		updateLaser();
		drawLaser(currentLaserState);
	}
	if (laserCounter == 99)
	{
		lazerMainFlag = false;
		laserCounter = 0;
		triggerRandomEvent();
	}

}


// SPEED TOKEN
void updateSpeedToken()
{
	myTokenRect = { obstacleToken.x , tempTokenY , 60 , 60 };
	if (obstacleToken.x < -150)
	{
		//while (myToken.x - myZapper.x < 50 || myToken.x - myZapper.x > -50)
		obstacleToken.x = 830 + rand() % 100;
		//while (myToken.y - myZapper.y < 50 || myToken.y - myZapper.y > -50)
		obstacleToken.y = 50 + rand() % 350;
		tempTokenY = obstacleToken.y;
	}
	obstacleToken.x += backVelocity;
}

void drawSpeedToken()
{
	if (!tokenFlag)
	{
		if (tokenCounter % 24 < 6)
		{
			SBDL::showTexture(obstacleToken.pic1, myTokenRect);
			tokenCounter++;
		}
		if (tokenCounter % 24 >= 6 && tokenCounter % 24 < 12)
		{
			SBDL::showTexture(obstacleToken.pic2, myTokenRect);
			tokenCounter++;
		}
		if (tokenCounter % 24 >= 12 && tokenCounter % 24 < 18)
		{
			SBDL::showTexture(obstacleToken.pic3, myTokenRect);
			tokenCounter++;
		}
		if (tokenCounter % 24 >= 18 && tokenCounter % 24 < 24)
		{
			SBDL::showTexture(obstacleToken.pic4, myTokenRect);
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
		drawBackGround();
		SBDL::showTexture(oldBarryGoFast, barryRect);
		int tokenElapsedTime = SBDL::getTime() - startTime;
		if (elapsedTime < delay)
		SBDL::delay(delay - tokenElapsedTime);
		SBDL::updateRenderScreen();
		}*/
	}
}

/*Manages the speed token functionality. Resets and triggers 
a random event when the speed token reaches a specific position. 
Updates and draws the speed token when the speedTokenMainFlag is true.*/
void handleSpeedToken()
{
	if (obstacleToken.x < -100 && obstacleToken.x > -150)
	{
		speedTokenMainFlag = false;
		obstacleToken.x = -200;
		triggerRandomEvent();
	}
	if (speedTokenMainFlag)
	{
		updateSpeedToken();
		drawSpeedToken();
	}
}

// GRAVITY TOEKN
void updateGravityToken()
{
	if (gravityTokenCore.x < -150)
	{
		gravityTokenCore.x = 850 + rand() % 100;
		gravityTokenCore.y = 30 + rand() % 350;

	}
	gravityTokenCore.x += backVelocity;
}

void drawGravityToken()
{
	GTokenRect = { gravityTokenCore.x , gravityTokenCore.y , 50 , 50 };
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

/*Manages the gravity token functionality. Resets and triggers 
a random event when the gravity token reaches a specific position. 
Updates and draws the gravity token when the gravityTokenMainFlag is true.*/
void handleGravityToken()
{
	if (gravityTokenCore.x < -100 && gravityTokenCore.x > -150)
	{
		gravityTokenMainFlag = false;
		gravityTokenCore.x = -200;
		triggerRandomEvent();
	}
	if (gravityTokenMainFlag)
	{
		updateGravityToken();
		drawGravityToken();
	}
}


// GAME OVER
void updateGameOverPage()
{
	SBDL::updateEvents();
	if (SBDL::mouseInRect(gameoverRetryRect) && SBDL::Mouse.clicked())
	{
		initializeGameVariables();
		currentGameState = STATE_PLAY;
	}
	else if (SBDL::mouseInRect(gameoverHomeRect) && SBDL::Mouse.clicked())
	{
		initializeGameVariables();
		currentGameState = STATE_HOME;
	}
}

void drawGameOverPage()
{
	fontTexture = SBDL::createFontTexture(scoreFont, std::to_string(score / 10), 0, 0, 0);
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

/*Updates and draws the game over page to display the game over screen.*/
void handleGameOverPage()
{
	updateGameOverPage();
	drawGameOverPage();
}


/*Displays the pause page with options to resume, go to the home menu, 
or retry the game. It shows the appropriate textures and checks
for mouse clicks to handle the corresponding actions.*/
void displayPausePage()
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
		currentGameState = STATE_PLAY;
	}

	else if (SBDL::mouseInRect(pausePageHomeRect) && SBDL::Mouse.clicked())
	{
		initializeGameVariables();
		currentGameState = STATE_HOME;
	}

	else if (SBDL::mouseInRect(retryRect) && SBDL::Mouse.clicked())
	{
		initializeGameVariables();
		currentGameState = STATE_PLAY;
	}
}