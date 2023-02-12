#include "BaseCharacter.h"
#include "raymath.h"


void BaseCharacter::Move(Vector2 inputValues)
{

	int MoveValue = (int)Velocity * (int)Acceleration;

	if (IsLimitedTop() || IsLimitedBottom())
	{
		inputValues.y = 0;
	}
	if (IsLimitedRight() || IsLimitedLeft())
	{
		inputValues.x = 0;
	}
	// Position += Vector2Multiply(Vector2{(float)MoveValue, (float)MoveValue}, inputValues);
	Vector2 MoveVector = Vector2{ (float)MoveValue, (float)MoveValue };
	Vector2 PositionInput = Vector2Multiply(MoveVector, inputValues);
	Position = Vector2Add(Position, PositionInput);

	DrawText(
		TextFormat("Coord X: %d \nCoord Y: %d", (int)Position.x, (int)Position.y),
		100,
		300,
		16,
		WHITE);
}

void BaseCharacter::Accelerate(bool active)
{
	if (active)
	{
		Acceleration += Acceleration < MAX_ACCELERATION ? 0.1f : 0.0f;
	}
	else
	{
		ResetAcceleration();
	}
}

void BaseCharacter::ResetAcceleration()
{
	Acceleration = InitialAcceleration;
}

bool BaseCharacter::IsLimitedRight()
{
	return true;
	// return Position.x >= controller.SCREEN_WIDTH - controller.SCREEN_MARGIN_BOTTOM_RIGHT;
}

bool BaseCharacter::IsLimitedLeft()
{
	return true;
	// return Position.x <= controller.SCREEN_MARGIN_TOP_LEFT;
}

bool BaseCharacter::IsLimitedTop()
{
	return true;
	// return Position.y <= (controller.SCREEN_MARGIN_TOP_LEFT);
}

bool BaseCharacter::IsLimitedBottom()
{
	return true;
	// return Position.y >= controller.SCREEN_HEIGHT - (controller.SCREEN_MARGIN_BOTTOM_RIGHT);
}

void BaseCharacter::Draw()
{
	DrawRectangle(
		(int)Position.x,
		(int)Position.y,
		(int)Size.x,
		(int)Size.y,
		WHITE);
}

// Setters
void BaseCharacter::SetSize(Vector2 size)
{
	Size = size;
}