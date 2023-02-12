#pragma once
#include "raylib.h"
#include "BasicCharacter.h"

class Bullet {
public:

	Bullet(
		Vector2 PositionInput,
		Vector2 DirectionInput,
		BasicCharacter* TargetInput
	);

	Vector2 Direction = { 0.f, 0.f };
	Vector2 Position = { 0.f, 0.f };
	Vector2 Size = { 20.f, 20.f };
	BasicCharacter* Target;

	bool spawned = false;
	bool impacted = false;
	bool destroyed = false;

	void Impact();
	void Move();

	void Draw();

};