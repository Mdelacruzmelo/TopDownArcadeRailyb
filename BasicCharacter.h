#pragma once
#include "raylib.h"
#include "screens.h"
#include "HealthComponent.h"
#include "Controller.h"

class BasicCharacter
{
public:

	Vector2 Position = Vector2{ 520, 540 };

	int screenLimitTop = 0;
	int screenLimitRight = 1080;
	int screenLimitBottom = 640;
	int screenLimitLeft = 0;

	int ammunition = 1000;
	int shots = 0;
	int bulletRate = 30;
	int bulletVelocity = 20;

	float opacity = 1;
	bool destroyed = false;
	bool beingDestroyed = false;

	void Move(Vector2 inputValues);
	void Accelerate(bool active);
	void ResetAcceleration();

	HealthComponent HealthComp = HealthComponent();
	Vector2 Size = { 20.f, 20.f };

	float Velocity = 1.f;
	float InitialAcceleration = 4.0f;
	float Acceleration = 4.0f;
	float MAX_ACCELERATION = 10.0f;

	void SetSize(Vector2 size);
	bool IsLimitedRight();
	bool IsLimitedLeft();
	bool IsLimitedTop();
	bool IsLimitedBottom();

	void Draw();
	void DrawHealthBar();
	void Shoot(
		Vector2 VehiclePosition,
		HealthComponent* HealthCompInput
	);
	bool IsAlive();
	void Destroy();
	void Explosion();
	void CheckDestroy();

};