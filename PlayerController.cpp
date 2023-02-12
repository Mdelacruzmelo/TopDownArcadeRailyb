#include "Controller.h"
#include "PlayerController.h"

PlayerController::PlayerController() {

	int limitTop = SCREEN_MARGIN_TOP_LEFT;
	int limitRight = SCREEN_WIDTH - SCREEN_MARGIN_BOTTOM_RIGHT;
	int limitBottom = SCREEN_HEIGHT - SCREEN_MARGIN_BOTTOM_RIGHT;
	int limitLeft = SCREEN_MARGIN_TOP_LEFT;

	character = new BasicCharacter(
		limitTop,
		limitRight,
		limitBottom,
		limitLeft
	);
}

void PlayerController::ListenAccelerateInput()
{
	bool buttonPressed = IsKeyDown(KEY_LEFT_SHIFT);
	character->Accelerate(buttonPressed);
}

void PlayerController::ListenMovementInputs()
{
	static Vector2 inputValues = { 0, 0 };
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S))
	{
		if (IsKeyDown(KEY_W)) inputValues.y = -1;
		if (IsKeyDown(KEY_S)) inputValues.y = 1;
	}
	else {
		inputValues.y = 0;
	}

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
	{
		if (IsKeyDown(KEY_A)) inputValues.x = -1;
		if (IsKeyDown(KEY_D)) inputValues.x = 1;
	}
	else {
		inputValues.x = 0;
	}

	character->Move(inputValues);
}


void PlayerController::Spawn() {
	character->Draw();
}