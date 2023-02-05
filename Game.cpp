#include "Game.h"
#include <iostream>
#include <string>

Game::Game() {
	vehiclePosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
	Velocity = 2.0f;
	Acceleration = 1.0f;
}

void Game::Start()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game started");
	SetTargetFPS(60);
	InitAudioDevice();

	while (!WindowShouldClose())
	{
		Move();
		BeginDrawing();
		ClearBackground(BLACK);

		DrawLevel();
		DrawVehicle();
		MoveLevel();

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}

void Game::DrawVehicle() {
	DrawRectangle(vehiclePosition.x, vehiclePosition.y, 20, 20, WHITE);
}

void Game::DrawLevel() {

	DrawMovingYRectanglesLeft(4);
	DrawMovingYRectanglesRight(3);

}

void Game::DrawMovingYRectanglesLeft(int quantity) {
	if (quantity == 0) return;
	static int* WidthsLeft = GetInitialWidthsLeft(quantity);
	static int* HeightsLeft = GetInitialHeightsLeft(quantity);
	static Color* RectangleColorsLeft = GetRandomColorsLeft(quantity);

	for (int i = 0; i < quantity; i++) {

		static int* YPositionsLeft = GetInitialYPointsLeft(quantity, HeightsLeft[i]);

		if (SCREEN_HEIGHT <= YPositionsLeft[i]) {
			RectangleColorsLeft[i] = GetRandomColor();
			WidthsLeft[i] = GetRandomValue(100, 310);
			HeightsLeft[i] = GetRandomValue(300, 500);
			YPositionsLeft[i] = -HeightsLeft[i];
		}
		else {
			YPositionsLeft[i] += LEVEL_ACCELERATION;
		}

		DrawRectangle(
			0,
			YPositionsLeft[i],
			WidthsLeft[i],
			HeightsLeft[i],
			RectangleColorsLeft[i]
		);
	}
}

void Game::DrawMovingYRectanglesRight(int quantity) {
	if (quantity == 0) return;
	// int rectHeight = 300;
	static int* Widths = GetInitialWidths(quantity);
	static int* Heights = GetInitialHeights(quantity);
	static Color* RectangleColors = GetRandomColors(quantity);

	for (int i = 0; i < quantity; i++) {

		static int* YPositions = GetInitialYPoints(quantity, Heights[i]);

		if (SCREEN_HEIGHT <= YPositions[i]) {
			RectangleColors[i] = GetRandomColor();
			Widths[i] = GetRandomValue(100, 310);
			Heights[i] = GetRandomValue(300, 500);
			YPositions[i] = -Heights[i];
		}
		else {
			YPositions[i] += LEVEL_ACCELERATION;
		}

		DrawRectangle(
			SCREEN_WIDTH - Widths[i],
			YPositions[i],
			Widths[i],
			Heights[i],
			RectangleColors[i]
		);
	}
}

int* Game::GetInitialYPointsLeft(int quantity, int height) {

	static int* RectangleYPositions = new int[quantity];

	for (int i = 0; i < quantity; i++) {
		RectangleYPositions[i] = -height * (i + 1);
	}

	return RectangleYPositions;
}

int* Game::GetInitialWidthsLeft(int quantity) {

	static int* WidthsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++) {
		WidthsLeft[i] = GetRandomValue(100, 250);
	}

	return WidthsLeft;
}

int* Game::GetInitialHeightsLeft(int quantity) {

	static int* HeightsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++) {
		HeightsLeft[i] = GetRandomValue(300, 500);
	}

	return HeightsLeft;
}

Color* Game::GetRandomColorsLeft(int quantity) {

	static Color* RandomColorsLeft = new Color[quantity];

	for (int i = 0; i < quantity; i++) {
		RandomColorsLeft[i] = GetRandomColor();
	}

	return RandomColorsLeft;
}

int* Game::GetInitialYPoints(int quantity, int height) {

	static int* RectangleYPositionsLeft = new int[quantity];

	for (int i = 0; i < quantity; i++) {
		RectangleYPositionsLeft[i] = -height * (i + 1);
	}

	return RectangleYPositionsLeft;
}

int* Game::GetInitialWidths(int quantity) {

	static int* Widths = new int[quantity];

	for (int i = 0; i < quantity; i++) {
		Widths[i] = GetRandomValue(100, 250);
	}

	return Widths;
}

int* Game::GetInitialHeights(int quantity) {

	static int* Hegiths = new int[quantity];

	for (int i = 0; i < quantity; i++) {
		Hegiths[i] = GetRandomValue(300, 500);
	}

	return Hegiths;
}

Color* Game::GetRandomColors(int quantity) {

	static Color* RandomColors = new Color[quantity];

	for (int i = 0; i < quantity; i++) {
		RandomColors[i] = GetRandomColor();
	}

	return RandomColors;
}


//void Game::DrawMovingYRectangles(int quantity) {
//
//	int RectangleWidth = 100;
//	int RectangleHeight = 300;
//	int RectangleXPosition = 0;
	// TODO: Preguntar como se hace un array dinamico que solo se setee 1 vez
//	static int RectangleYPositions[4] = { -300, -600, -900, -1200 };
//
//	Color Colors[4] = { YELLOW, ORANGE, RED, GREEN };
//
//	static Color RectangleColors[4] = {
//		Colors[GetRandomValue(0,3)],
//		Colors[GetRandomValue(0,3)],
//		Colors[GetRandomValue(0,3)],
//		Colors[GetRandomValue(0,3)]
//	};
//
//	for (int i = 0; i < 3; i++) {
//
//		if (SCREEN_HEIGHT <= RectangleYPositions[i]) {
//			RectangleYPositions[i] = -RectangleHeight;
//			RectangleColors[i] = Colors[GetRandomValue(0, 3)];
//		}
//		else {
//			RectangleYPositions[i] += LEVEL_ACCELERATION;
//		}
//
//		DrawRectangle(
//			RectangleXPosition,
//			RectangleYPositions[i],
//			RectangleWidth,
//			RectangleHeight,
//			Colors[i]
//		);
//	}
//
//}

void Game::MoveLevel() {
	LevelPosY += LEVEL_ACCELERATION;
}

void Game::Move() {

	int MoveValue = (int)Velocity * Acceleration;

	if (IsKeyDown(KEY_W)) {
		vehiclePosition.y -= IsLimitedTop()
			? 0
			: MoveValue;
	}
	if (IsKeyDown(KEY_S)) {
		vehiclePosition.y += IsLimitedBottom()
			? 0
			: MoveValue;
	}
	if (IsKeyDown(KEY_D)) {
		vehiclePosition.x += IsLimitedRight()
			? 0
			: MoveValue;
	}
	if (IsKeyDown(KEY_A)) {
		vehiclePosition.x -= IsLimitedLeft()
			? 0
			: MoveValue;
	}

	Accelerate();
}

void Game::Accelerate() {
	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		Acceleration += Acceleration < MAX_ACCELERATION ? 0.1f : 0.0f;
	}
	else ResetAcceleration();
}

void Game::ResetAcceleration() {
	Acceleration = InitialAcceleration;
}

bool Game::IsLimitedRight() {
	return vehiclePosition.x >= SCREEN_WIDTH - SCREEN_MARGIN_BOTTOM_RIGHT;
}

bool Game::IsLimitedLeft() {
	return vehiclePosition.x <= SCREEN_MARGIN_TOP_LEFT;
}

bool Game::IsLimitedTop() {
	return vehiclePosition.y <= (SCREEN_MARGIN_TOP_LEFT);
}

bool Game::IsLimitedBottom() {
	return vehiclePosition.y >= SCREEN_HEIGHT - (SCREEN_MARGIN_BOTTOM_RIGHT);
}

Color Game::GetRandomColor() {
	return Colors[GetRandomValue(0, 11)];
}