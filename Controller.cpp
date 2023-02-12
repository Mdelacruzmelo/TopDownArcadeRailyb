#include "Controller.h"

Controller::Controller() {

}

Controller::Controller(
	int screenWidth,
	int screenHeight,
	int marginTopLeft,
	int marginBottomRight)
{

	SCREEN_WIDTH = screenWidth;
	SCREEN_HEIGHT = screenHeight;
	SCREEN_MARGIN_TOP_LEFT = marginTopLeft;
	SCREEN_MARGIN_BOTTOM_RIGHT = marginBottomRight;
}

void Controller::ListenAccelerateInput()
{
}

void Controller::ListenMovementInputs()
{
	static Vector2 inputValues = { 0, 0 };
	if (IsKeyDown(KEY_W))
	{
		// inputValues.y = -1;
	}
	if (IsKeyDown(KEY_S))
	{
		// inputValues.y = 1;
	}
	if (IsKeyDown(KEY_D))
	{
		// inputValues.x = 1;
	}
	if (IsKeyDown(KEY_A))
	{
		// inputValues.x = -1;
	}
	// Character do something
	// return inputValues;
}