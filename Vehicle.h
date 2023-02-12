#pragma once
#include "raylib.h"
#include "screens.h"
#include "Vehicle.utils.h"

class Vehicle
{
public:
	Vehicle(E_VehicleType Type);
	void Draw();
	void Draw(Vector2 Position);

private:
	E_VehicleType Type = VEHICLE_STANDARD;

	float Health;
	float Shield;
	int Speed;
	float Attack;

	Vector2 InitialPosition = Vector2{ 100, 100 };
	Vector2 Size;
};