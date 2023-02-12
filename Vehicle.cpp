#include "Vehicle.h"

Vehicle::Vehicle(E_VehicleType Type)
{
	switch (Type)
	{
	case VEHICLE_HEAVY:
		Health = 400.0f;
		Shield = 100.0f;
		Speed = 2;
		Attack = 10;
		Size = { 60, 80 };
		break;

	case VEHICLE_LIGHT:
		Health = 50.0f;
		Shield = 50.0f;
		Speed = 8;
		Attack = 2;
		Size = { 30, 40 };
		break;

	case VEHICLE_STANDARD:
	default:
		Health = 100.0f;
		Shield = 100.0f;
		Speed = 4;
		Attack = 5;
		Size = { 40, 60 };
		break;
	}
};

void Vehicle::Draw(Vector2 Position)
{
	DrawRectangle((int)Position.x, (int)Position.y, (int)Size.x, (int)Size.y, WHITE);
}

void Vehicle::Shoot()
{

}

void Vehicle::Move()
{
	if (bIsGoingRight) {
		Position.x += Velocity * 1;
		if (Position.x >= TargetLocation.x) SetNextTargetLocation();
	}
	else {
		Position.x -= Velocity * 1;
		if (Position.x <= TargetLocation.x) SetNextTargetLocation();
	}
}

void Vehicle::SetNextTargetLocation()
{
	if (bIsGoingRight) {
		bIsGoingRight = false;
		TargetLocation.x = 100;
	}
	else {
		bIsGoingRight = true;
		TargetLocation.x = 400;
	}
}

void Vehicle::Draw()
{
	DrawRectangle(
		(int)Position.x,
		(int)Position.y,
		(int)Size.x,
		(int)Size.y,
		GREEN
	);
}