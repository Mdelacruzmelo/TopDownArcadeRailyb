#pragma once
#include "raylib.h"
#include "screens.h"
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

	E_VehicleType Type = VEHICLE_STANDARD;

	float Health;
	float Shield;
	int Speed;
	float Attack;
	int Velocity = 2;

	bool bInTarget = false;
	bool bIsGoingRight = true;

	Vector2 TargetLocation = Vector2{ 400.f, 100.f };
	Vector2 Position = Vector2{ 100.f, 100.f };
	Vector2 Size;

};