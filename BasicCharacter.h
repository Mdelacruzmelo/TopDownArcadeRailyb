#pragma once
#include "raylib.h"
#include "screens.h"

class BasicCharacter
{
public:

	BasicCharacter();
	BasicCharacter(
		int limitTop,
		int limitRight,
		int limitBottom,
		int limitLeft
	);
	Vector2 Position = Vector2{ 520, 540 };

	int screenLimitTop;
	int screenLimitRight;
	int screenLimitBottom;
	int screenLimitLeft;

	void Move(Vector2 inputValues);
	void Accelerate(bool active);
	void ResetAcceleration();

	float Velocity = 1.f;
	float InitialAcceleration = 4.0f;
	float Acceleration = 4.0f;
	float MAX_ACCELERATION = 10.0f;

	bool IsLimitedRight();
	bool IsLimitedLeft();
	bool IsLimitedTop();
	bool IsLimitedBottom();
	void Draw();

	// Setters
	void SetSize(Vector2 size);
	Vector2 Size = { 20.f, 20.f };
};