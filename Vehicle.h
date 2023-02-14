#pragma once
#include "raylib.h"
#include "screens.h"
#include "Bullet.h"
#include "BasicCharacter.h"
#include "Vehicle.utils.h"

class Vehicle
{
public:
	Vehicle(E_VehicleType Type);
	void Draw();
	void Draw(Vector2 PositionInput);
	void Shoot();
	void Move();
	void SetNextTargetLocation();
	void SetTarget(BasicCharacter* TargetInput);

	E_VehicleType Type = VEHICLE_STANDARD;

	float Health;
	float Shield;
	int Speed;
	float Attack;
	int Velocity = 5;

	bool bInTarget = false;
	bool bIsGoingRight = true;
	bool shooted = false;

	BasicCharacter* Target;
	Vector2 TargetLocation = Vector2{ 800.f, 100.f };
	Vector2 Position = Vector2{ 100.f, 100.f };
	Vector2 Size;

	Bullet* bullet;

};