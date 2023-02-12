#include "BasicCharacter.h"
#include "raymath.h"

BasicCharacter::BasicCharacter(
	int limitTop,
	int limitRight,
	int limitBottom,
	int limitLeft
) {
	screenLimitTop = limitTop;
	screenLimitRight = limitRight;
	screenLimitBottom = limitBottom;
	screenLimitLeft = limitLeft;
}

void BasicCharacter::Move(Vector2 inputValues)
{
	int MoveValue = (int)Velocity * (int)Acceleration;

	if (IsLimitedTop() && inputValues.y == -1)
	{
		inputValues.y = 0;
	}
	if (IsLimitedBottom() && inputValues.y == 1)
	{
		inputValues.y = 0;
	}
	if (IsLimitedRight() && inputValues.x == 1)
	{
		inputValues.x = 0;
	}
	if (IsLimitedLeft() && inputValues.x == -1)
	{
		inputValues.x = 0;
	}

	Vector2 MoveVector = Vector2{ (float)MoveValue, (float)MoveValue };
	Vector2 PositionInput = Vector2Multiply(MoveVector, inputValues);
	Position = Vector2Add(Position, PositionInput);

	DrawText(
		TextFormat(
			"Coord X: %d \nCoord Y: %d \ Limit TOP: %d \ Limit BOTTOM: %d",
			(int)Position.x,
			(int)Position.y,
			(int)screenLimitTop,
			(int)screenLimitBottom
		),
		100,
		300,
		16,
		WHITE);
}

void BasicCharacter::Accelerate(bool active)
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

void BasicCharacter::ResetAcceleration()
{
	Acceleration = InitialAcceleration;
}

bool BasicCharacter::IsLimitedRight()
{
	return false;
	// return Position.x >= screenLimitRight;
}

bool BasicCharacter::IsLimitedLeft()
{
	// return false;
	return Position.x <= screenLimitLeft;
}

bool BasicCharacter::IsLimitedTop()
{
	return Position.y <= screenLimitTop;
}

bool BasicCharacter::IsLimitedBottom()
{
	return Position.y >= screenLimitBottom;
}

void BasicCharacter::Draw()
{
	DrawRectangle(
		(int)Position.x,
		(int)Position.y,
		(int)Size.x,
		(int)Size.y,
		WHITE);
}

// Setters
void BasicCharacter::SetSize(Vector2 size)
{
	Size = size;
}