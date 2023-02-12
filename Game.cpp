#include "Game.h"
#include "Vehicle.h"
#include "PlayerController.h"
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

	// Vehicle EnemyStandard = Vehicle(VEHICLE_STANDARD);
	// Vehicle EnemyHeavy = Vehicle(VEHICLE_HEAVY);253880
	// Vehicle EnemyLight = Vehicle(VEHICLE_LIGHT);253880

	while (!WindowShouldClose())
	{

		BeginDrawing();
		ClearBackground(BLACK);

		PLAYER.Spawn();
		PLAYER.ListenMovementInputs();
		PLAYER.ListenAccelerateInput();

		// EnemyStandard.Draw(Vector2{300, 200});
		// EnemyHeavy.Draw(Vector2{370, 200});
		// EnemyHeavy.Draw(Vector2{500, 250});
		// EnemyLight.Draw(Vector2{200, 100});

		DrawLevel();
		MoveLevel();

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}

void Game::DrawLevel()
{
	DrawMovingYRectanglesLeft(4);
	DrawMovingYRectanglesRight(3);
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

// Dibujar rectangulos a la izquierda
void Game::DrawMovingYRectanglesLeft(int quantity)
{

	// TODO: Preguntar una mejor manera de usar la misma function con static 
	// Guardo un array de anchos y altos y 
	// Itero entre ellos y los voy modificando si han pasado la pantalla
	if (quantity == 0) {
		return;
	}

	static int* WidthsLeft = GetInitialWidthsLeft(quantity);
	static int* HeightsLeft = GetInitialHeightsLeft(quantity);
	static Color* RectangleColorsLeft = GetRandomColorsLeft(quantity);

	for (int i = 0; i < quantity; i++)
	{

		static int* YPositionsLeft = GetInitialYPointsLeft(quantity, HeightsLeft[i]);

		if (SCREEN_HEIGHT <= YPositionsLeft[i])
		{
			RectangleColorsLeft[i] = GetRandomColor();
			WidthsLeft[i] = GetRandomValue(100, 310);
			HeightsLeft[i] = GetRandomValue(300, 500);
			YPositionsLeft[i] = -HeightsLeft[i];
		}
		else
		{
			YPositionsLeft[i] += (int)LEVEL_ACCELERATION;
		}

		DrawRectangle(
			0,
			YPositionsLeft[i],
			WidthsLeft[i],
			HeightsLeft[i],
			RectangleColorsLeft[i]);
	}
}

// Dibujar rectangulos a la derecha
void Game::DrawMovingYRectanglesRight(int quantity)
{
	if (quantity == 0)
		return;
	static int* Widths = GetInitialWidths(quantity);
	static int* Heights = GetInitialHeights(quantity);
	static Color* RectangleColors = GetRandomColors(quantity);

	for (int i = 0; i < quantity; i++)
	{

		static int* YPositions = GetInitialYPoints(quantity, Heights[i]);

		if (SCREEN_HEIGHT <= YPositions[i])
		{
			RectangleColors[i] = GetRandomColor();
			Widths[i] = GetRandomValue(100, 310);
			Heights[i] = GetRandomValue(300, 500);
			YPositions[i] = -Heights[i];
		}
		else
		{
			YPositions[i] += (int)LEVEL_ACCELERATION;
		}

		DrawRectangle(
			SCREEN_WIDTH - Widths[i],
			YPositions[i],
			Widths[i],
			Heights[i],
			RectangleColors[i]);
	}
}

int* Game::GetInitialYPointsLeft(int quantity, int height)
{

	static int* RectangleYPositions = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		RectangleYPositions[i] = -height * (i + 1);
	}

	return RectangleYPositions;
}

int* Game::GetInitialWidthsLeft(int quantity)
{

	static int* WidthsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		WidthsLeft[i] = GetRandomValue(100, 250);
	}

	return WidthsLeft;
}

int* Game::GetInitialHeightsLeft(int quantity)
{

	static int* HeightsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		HeightsLeft[i] = GetRandomValue(300, 500);
	}

	return HeightsLeft;
}

Color* Game::GetRandomColorsLeft(int quantity)
{

	static Color* RandomColorsLeft = new Color[quantity];

	for (int i = 0; i < quantity; i++)
	{
		RandomColorsLeft[i] = GetRandomColor();
	}

	return RandomColorsLeft;
}

int* Game::GetInitialYPoints(int quantity, int height)
{

	static int* RectangleYPositionsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		RectangleYPositionsLeft[i] = -height * (i + 1);
	}

	return RectangleYPositionsLeft;
}

int* Game::GetInitialWidths(int quantity)
{

	static int* Widths = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		Widths[i] = GetRandomValue(100, 250);
	}

	return Widths;
}

int* Game::GetInitialHeights(int quantity)
{

	static int* Hegiths = new int[quantity];

	for (int i = 0; i < quantity; i++)
	{
		Hegiths[i] = GetRandomValue(300, 500);
	}

	return Hegiths;
}

Color* Game::GetRandomColors(int quantity)
{

	static Color* RandomColors = new Color[quantity];

	for (int i = 0; i < quantity; i++)
	{
		RandomColors[i] = GetRandomColor();
	}

	return RandomColors;
}

void Game::MoveLevel()
{
	LevelPosY += (int)LEVEL_ACCELERATION;
}

Color Game::GetRandomColor()
{
	return Colors[GetRandomValue(0, 11)];
}