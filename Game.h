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
	int LevelPosY = 0;
	bool paused = false;
	float TimePassed = 0;

private:

	void DrawLevel();
	void DrawProgressBar();
	void DrawMovingYRectangles(int quantity);
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