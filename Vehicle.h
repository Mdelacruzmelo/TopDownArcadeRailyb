#pragma once
#include "raylib.h"
#include "screens.h"
#include "BasicCharacter.h"
#include "Vehicle.utils.h"
#include "HealthComponent.h"

class Vehicle
{
public:
	Vehicle();
	Vehicle(E_VehicleType TypeInput);

	E_VehicleType Type = VEHICLE_STANDARD;
	BasicCharacter* Target;
	Vector2 TargetLocation = Vector2{ 800.f, 100.f };
	Vector2 Position = Vector2{ 100.f, 100.f };
	Vector2 Size;

	HealthComponent HealthComp = HealthComponent();
	HealthComponent* GetHealthComp();

	int Speed;
	int AttackDamage = 10;
	int Velocity = 5;
	bool bIsGoingRight = true;

	int startBulletRate = 0;
	int bulletRate = 100;
	int ammunition = 1000;
	int shots = 1;
	int bulletVelocity = 10;

	float opacity = 1;
	bool destroyed = false;
	bool beingDestroyed = false;

	void Draw();
	void DrawHealthBar();
	void Draw(Vector2 PositionInput);
	Vector2 GetPosition();

	void Shoot();
	void CheckShootFaster();
	void Move();
	void SetNextTargetLocation();
	void SetTarget(BasicCharacter* TargetInput);
	bool IsAlive();
	void Destroy();
	void Explosion();
	void CheckDestroy();
};