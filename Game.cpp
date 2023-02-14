#include "Game.h"
#include "Vehicle.h"
#include "PlayerController.h"
#include "AIController.h"
#include <iostream>
#include <string>

Game::Game()
{
	// vehiclePosition = {(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
	// Velocity = 2.0f;
	// Acceleration = 1.0f;
}

void Game::Start()
{

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game started");
	SetTargetFPS(60);
	InitAudioDevice();

	PlayerController PLAYER = PlayerController();
	BasicCharacter* EnemyTarget = PLAYER.getCharacter();
	AIController ENEMY = AIController(EnemyTarget);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		PLAYER.Spawn();
		PLAYER.ListenMovementInputs();
		PLAYER.ListenShootInput();
		PLAYER.ListenAccelerateInput();

		ENEMY.SpawnVehicle();

		DrawLevel();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}

void Game::DrawLevel()
{
	LevelPosY += (int)LEVEL_ACCELERATION;
	DrawMovingYRectangles(4);
	DrawProgressBar();
}

void Game::DrawProgressBar()
{
	float GrowAlpha = (float)(GetTime() / LEVEL_TIME);
	float Progress = SCREEN_WIDTH * GrowAlpha;

	DrawText(
		TextFormat("Time: %d", (int)GetTime()),
		100,
		540,
		16,
		WHITE);
	DrawText(
		TextFormat("Time: %f", (float)(GrowAlpha)),
		100,
		580,
		16,
		WHITE);

	DrawRectangle(0, 0, (int)Progress, 20, WHITE);
}

void Game::DrawMovingYRectangles(int quantity)
{
	if (quantity == 0) return;

	// Draw rectangles on the left side 

	static int* WidthsLeft = new int[quantity];
	static int* HeightsLeft = new int[quantity];
	static Color* RectangleColorsLeft = new Color[quantity];
	static bool* startedLeft = new bool[quantity];
	static int* YPositionsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		if (startedLeft[i] != true) {

			WidthsLeft[i] = GetRandomValue(100, 250);
			HeightsLeft[i] = GetRandomValue(300, 500);
			RectangleColorsLeft[i] = GetRandomColor();
			startedLeft[i] = true;
			YPositionsLeft[i] = -HeightsLeft[i] * (i + 1);
		}
		else {

			if (SCREEN_HEIGHT <= YPositionsLeft[i])
			{
				RectangleColorsLeft[i] = GetRandomColor();
				WidthsLeft[i] = GetRandomValue(100, 310);
				HeightsLeft[i] = GetRandomValue(300, 500);
				YPositionsLeft[i] = -HeightsLeft[i];
			}
			else YPositionsLeft[i] += (int)LEVEL_ACCELERATION;

			DrawRectangle(
				0,
				YPositionsLeft[i],
				WidthsLeft[i],
				HeightsLeft[i],
				RectangleColorsLeft[i]);

		}
	}

	// Draw rectangles on the right side 

	static int* WidthsRight = new int[quantity];
	static int* HeightsRight = new int[quantity];
	static Color* RectangleColorsRight = new Color[quantity];
	static bool* startedRight = new bool[quantity];
	static int* YPositionsRight = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		if (startedRight[i] != true) {

			WidthsRight[i] = GetRandomValue(100, 250);
			HeightsRight[i] = GetRandomValue(300, 500);
			RectangleColorsRight[i] = GetRandomColor();
			startedRight[i] = true;
			YPositionsRight[i] = -HeightsRight[i] * (i + 1);

		}
		else {

			if (SCREEN_HEIGHT <= YPositionsRight[i])
			{
				RectangleColorsRight[i] = GetRandomColor();
				WidthsRight[i] = GetRandomValue(100, 310);
				HeightsRight[i] = GetRandomValue(300, 500);
				YPositionsRight[i] = -HeightsRight[i];
			}
			else YPositionsRight[i] += (int)LEVEL_ACCELERATION;

			DrawRectangle(
				SCREEN_WIDTH - WidthsRight[i],
				YPositionsRight[i],
				WidthsRight[i],
				HeightsRight[i],
				RectangleColorsRight[i]);
		}

	}

}

Color Game::GetRandomColor()
{
	return Colors[GetRandomValue(0, 11)];
}