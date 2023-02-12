#pragma once
#include "Controller.h"
#include "raylib.h"
#include "screens.h"

class BaseCharacter
{
public:

	void Move(Vector2 inputValues);
	void Accelerate(bool active);
	void ResetAcceleration();

	Vector2 Position = Vector2{ 120.f, 120.f };
	// Controller controller;

	float Velocity = 1.f;
	float InitialAcceleration = 4.0f;
	float Acceleration = 1.f;
	float MAX_ACCELERATION = 10.0f;

	bool IsLimitedRight();
	bool IsLimitedLeft();
	bool IsLimitedTop();
	bool IsLimitedBottom();
	void Draw();

	// Setters
	void SetSize(Vector2 size);

private:
	Vector2 Size = { 20.f, 20.f };
};