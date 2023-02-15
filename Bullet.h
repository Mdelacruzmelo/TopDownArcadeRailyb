#pragma once
#include "raylib.h"
#include "BasicCharacter.h"
#include "Vehicle.h"
#include "HealthComponent.h"

class Bullet {
public:
	Bullet();
	Bullet(
		Vector2 OriginInput,
		Vector2 DirectionInput,
		BasicCharacter* TargetInput,
		int quantity,
		int shoots,
		int velocity,
		int damage
	);
	Bullet(
		Vector2 OriginInput,
		Vector2 DirectionInput,
		int quantity,
		int shoots,
		int velocity,
		Vector2 VehiclePosition,
		HealthComponent* HealthCompInput
	);

	int BulletVelocity = 5;
	Vector2 Size = { 8.f, 25.f };
	BasicCharacter* Target;
};