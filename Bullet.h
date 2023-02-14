#pragma once
#include "raylib.h"
#include "BasicCharacter.h"

class Bullet {
public:
	Bullet(
		Vector2 PositionInput,
		Vector2 DirectionInput,
		BasicCharacter* TargetInput,
		int quantity
	);

	int BulletVelocity = 5;
	Vector2 Size = { 8.f, 25.f };
	BasicCharacter* Target;
};