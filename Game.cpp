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
	BasicCharacter* Character = PlayerControl.getCharacter();

	AIController EnemyControl = AIController(Character); // Set ref to our enemy
	Vehicle* VehicleTarget = EnemyControl.getVehiclePawn();

	PlayerControl.SetTarget(VehicleTarget);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_Q)) paused = !paused;

		BeginDrawing();

		ClearBackground(BLACK);

		if (inMainMenu) DrawMainMenu();
		else if (inLooseScreen) DrawLooseScreen();
		else if (inControls) DrawControls();
		else if (inSuccessScreen) DrawSuccessScreen();
		else if (playing) {

			DrawLevel();

			if (Character->HealthComp.GetHealth() <= 0 || ProgressBar >= 100) {

				SoundLooseTheme();
				forceStopProgressBar = true;

				static int destroyTime = 0;
				destroyTime += 1;

				if (destroyTime >= 100) {
					if (ProgressBar >= 100) {
						loosedByTime = true;
					}
					playing = false;
					inLooseScreen = true;
				}
			}
			else if (VehicleTarget->HealthComp.GetHealth() <= 0) {

				SoundSuccessTheme();
				forceStopProgressBar = true;

				static int enjoyTime = 0;
				enjoyTime += 1;

				if (enjoyTime >= 100) {
					playing = false;
					inSuccessScreen = true;
				}

			}

			PlayerControl.Spawn();
			EnemyControl.SpawnVehicleStandard();

			if (paused) {
				LEVEL_ACCELERATION = 0;
				DrawPauseMenu();
			}
			else {
				LEVEL_ACCELERATION = INITIAL_LEVEL_ACCELERATION;

				PlayerControl.ListenMovementInputs();
				PlayerControl.ListenAccelerateInput();
				PlayerControl.ListenShootInput(VehicleTarget->GetHealthComp());

				EnemyControl.Play();
			}
		}

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}

void Game::DrawPauseMenu() {

	DrawRectangle(
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		Fade(BLACK, 0.5));

	DrawText(
		TextFormat("Pause"),
		220,
		405,
		40,
		WHITE);

}

void Game::DrawControls() {

	LoadTimePassed += GetFrameTime();

	float GrowAlpha = (float)(LoadTimePassed / LOADING_TIME);
	float BarWidth = SCREEN_WIDTH * GrowAlpha;
	LoadingBar = (int)((BarWidth * 100) / SCREEN_WIDTH);

	DrawRectangle(0, 10, (int)BarWidth, 15, WHITE);

	DrawText(
		TextFormat("Loading: %d %", (int)LoadingBar),
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

	DrawText(
		TextFormat("Movement: A W S D \nShoot: SPACE\nSpeed: L Shift\nPause: Q"),
		220,
		405,
		20,
		WHITE);

	DrawText(
		TextFormat("Kill the enemy before the \nprogress bar goes to 100%"),
		220,
		205,
		30,
		WHITE);

	// Skip button
	DrawRectangle(
		900,
		600,
		100,
		40,
		GRAY);

	DrawText(
		TextFormat("Skip"),
		920,
		605,
		30,
		BLACK);

	if (
		IsMouseButtonPressed(0) &&
		GetMouseX() >= 900 &&
		GetMouseX() <= (900 + 100) &&
		GetMouseY() >= 600 &&
		GetMouseY() <= (600 + 40)
		) {
		playing = true;
		inControls = false;
	}

	if (LoadingBar >= 100) {
		inControls = false;
	}
}

void Game::DrawSuccessScreen() {

	static int timeInSuccessScreen = 0;
	timeInSuccessScreen += 1;

	DrawRectangle(
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		Fade(BLACK, 0.5));

	DrawText(
		TextFormat("You W-I-N !"),
		220,
		405,
		40,
		WHITE);

	if (timeInSuccessScreen >= 150) {
		CloseWindow();
	}
}

void Game::DrawMainMenu()
{
	static int buttonPosX = 200;
	static int buttonPosY = 400;
	static int buttonWidth = 120;
	static int buttonHeight = 40;

	DrawRectangle(
		buttonPosX,
		buttonPosY,
		buttonWidth,
		buttonHeight,
		WHITE);

	DrawText(
		TextFormat("Play"),
		buttonPosX + 20,
		buttonPosY + 5,
		buttonHeight - 10,
		BLACK);

	if (
		IsMouseButtonPressed(0) &&
		GetMouseX() >= buttonPosX &&
		GetMouseX() <= (buttonPosX + buttonWidth) &&
		GetMouseY() >= buttonPosY &&
		GetMouseY() <= (buttonPosY + buttonHeight)
		) {
		inControls = true;
		playing = true;
		inMainMenu = false;
	}
}

void Game::SoundSuccessTheme() {

	static bool setOnce = false;

	if (!setOnce) {
		successSound = LoadSound("resources/SuccessTheme.wav");
		StopSound(levelSound);
		SetSoundVolume(successSound, 0.6);
		PlaySound(successSound);
		setOnce = true;
	}

}

void Game::SoundLooseTheme() {

	static bool setOnce = false;

	if (!setOnce) {
		looseSound = LoadSound("resources/LooseTheme.wav");
		StopSound(levelSound);
		SetSoundVolume(looseSound, 0.5);
		PlaySound(looseSound);
		setOnce = true;
	}

}

void Game::DrawLooseScreen()
{
	static int timeInLooseScreen = 0;
	timeInLooseScreen += 1;

	DrawRectangle(
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		Fade(BLACK, 0.5));

	if (loosedByTime) {
		DrawText(
			TextFormat("Time finished"),
			220,
			405,
			40,
			WHITE);
	}
	else {
		DrawText(
			TextFormat("You loose"),
			220,
			405,
			40,
			WHITE);
	}

	if (timeInLooseScreen >= 300) {
		CloseWindow();
	}
}

void Game::DrawLevel()
{
	static bool setOnce = false;

	if (!setOnce) {
		levelSound = LoadSound("resources/TetrisTheme.wav");

		SetSoundVolume(levelSound, 0.05);
		PlaySound(levelSound);
		setOnce = true;
	}

	DrawMovingYRectangles(4);
	DrawProgressBar();
}

void Game::DrawProgressBar()
{
	if (!paused && !forceStopProgressBar) {
		TimePassed += GetFrameTime();
	}

	float GrowAlpha = (float)(TimePassed / LEVEL_TIME);
	float BarWidth = SCREEN_WIDTH * GrowAlpha;
	ProgressBar = (int)((BarWidth * 100) / SCREEN_WIDTH);

	DrawRectangle(0, 0, SCREEN_WIDTH, 35, BLACK);

	DrawRectangle(0, 10, (int)BarWidth, 15, WHITE);

	DrawText(
		TextFormat("Progress: %d %", (int)ProgressBar),
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