#pragma once
#include "raylib.h"
#include "screens.h"
#include <string>

class Game
{
public:

	void Start();

	int SCREEN_WIDTH = 1080;
	int SCREEN_HEIGHT = 720;
	float SCREEN_MARGIN_TOP_LEFT = 30;
	float SCREEN_MARGIN_BOTTOM_RIGHT = 50;
	float INITIAL_LEVEL_ACCELERATION = 24.0f;
	float LEVEL_ACCELERATION = 24.0f;
	int LEVEL_TIME = 30;
	int LOADING_TIME = 10;
	int LevelPosY = 0;
	bool paused = false;
	float TimePassed = 0;
	float LoadTimePassed = 0;

	bool playing = false;
	bool inMainMenu = true;
	bool inLooseScreen = false;
	bool loosedByTime = false;
	bool inControls = false;
	bool inSuccessScreen = false;
	bool forceStopProgressBar = false;

	int ProgressBar = 0;
	int LoadingBar = 0;

	Sound levelSound;
	Sound looseSound;
	Sound successSound;

private:

	void DrawControls();
	void DrawMainMenu();
	void DrawPauseMenu();
	void DrawLooseScreen();
	void DrawSuccessScreen();
	void DrawLevel();
	void DrawProgressBar();
	void DrawMovingYRectangles(int quantity);
	void SoundLooseTheme();
	void SoundSuccessTheme();

	Color GetRandomColor();
	Color Colors[11] = {
		LIGHTGRAY,
		GRAY,
		DARKGRAY,
		YELLOW,
		GOLD,
		ORANGE,
		PINK,
		RED,
		MAROON,
		GREEN,
		LIME,
	};
};