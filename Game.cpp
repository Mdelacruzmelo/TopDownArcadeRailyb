#include "Game.h"
#include "Vehicle.h"
#include "PlayerController.h"
#include "AIController.h"
#include "HealthComponent.h"
#include <iostream>
#include <string>

void Game::Start()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game started");
	SetTargetFPS(60);
	InitAudioDevice();

	PlayerController PlayerControl = PlayerController();
	BasicCharacter* EnemyTarget = PlayerControl.getCharacter();
	AIController EnemyControl = AIController(EnemyTarget);
	Vehicle* VehicleTarget = EnemyControl.getVehiclePawn();
	PlayerControl.SetTarget(VehicleTarget);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_Q)) paused = !paused;

		BeginDrawing();
		ClearBackground(BLACK);
		DrawLevel();

		PlayerControl.Spawn();
		EnemyControl.SpawnVehicleStandard();

		if (paused) {

			LEVEL_ACCELERATION = 0;

		}
		else {

			LEVEL_ACCELERATION = INITIAL_LEVEL_ACCELERATION;

			PlayerControl.ListenMovementInputs();
			PlayerControl.ListenAccelerateInput();
			PlayerControl.ListenShootInput(VehicleTarget->GetHealthComp());

			EnemyControl.Play();
		}

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}

void Game::DrawLevel()
{
	DrawMovingYRectangles(4);
	DrawProgressBar();
}

void Game::DrawProgressBar()
{
	if (!paused) {
		TimePassed += GetFrameTime();
	}

	float GrowAlpha = (float)(TimePassed / LEVEL_TIME);
	float BarWidth = SCREEN_WIDTH * GrowAlpha;
	int Progress = (int)((BarWidth * 100) / SCREEN_WIDTH);

	DrawRectangle(0, 0, SCREEN_WIDTH, 35, BLACK);

	DrawRectangle(0, 10, (int)BarWidth, 15, WHITE);

	DrawText(
		TextFormat("Progress: %d %", (int)Progress),
		20,
		10,
		15,
		BLACK);
	// Esto es un apanyo porque no sé como pintar "10%", solo pinta "10"
	DrawText(
		"%",
		115,
		10,
		15,
		BLACK);

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