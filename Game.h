#pragma once
#include "raylib.h"
#include "screens.h"
#include <string>

class Game
{
public:

	Game();
	void Start();

	int SCREEN_WIDTH = 1080;
	int SCREEN_HEIGHT = 720;
	float SCREEN_MARGIN_TOP_LEFT = 30;
	float SCREEN_MARGIN_BOTTOM_RIGHT = 50;
	int LevelPosY = 0;
	float LEVEL_ACCELERATION = 24.0f;

private:

	void Move();
	void MoveLevel();
	void Accelerate();
	void ResetAcceleration();

	Vector2 vehiclePosition;

	float Velocity;
	float InitialAcceleration = 4.0f;
	float Acceleration;

	float MAX_ACCELERATION = 10.0f;



	bool IsLimitedRight();
	bool IsLimitedLeft();
	bool IsLimitedTop();
	bool IsLimitedBottom();

	void DrawLevel();
	void DrawVehicle();

	// TODO: Preguntar una mejor manera de usar la misma function con static dentro 
	void DrawMovingYRectanglesLeft(int quantity);
	void DrawMovingYRectanglesRight(int quantity);

	int* GetInitialYPointsLeft(int initY, int height);
	int* GetInitialYPoints(int initY, int height);

	int* GetInitialWidths(int initY);
	int* GetInitialWidthsLeft(int initY);

	int* GetInitialHeightsLeft(int initY);
	int* GetInitialHeights(int initY);

	Color* GetRandomColorsLeft(int initY);
	Color* GetRandomColors(int initY);

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
		/*DARKGREEN,
		SKYBLUE,
		BLUE,
		DARKBLUE,
		PURPLE,
		VIOLET,
		DARKPURPLE,
		BEIGE,
		BROWN,
		DARKBROWN,
		WHITE,
		BLACK,
		BLANK,
		MAGENTA,
		RAYWHITE*/
	};
};