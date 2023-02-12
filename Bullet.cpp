#include "Bullet.h"

Bullet::Bullet(
	Vector2 PositionInput,
	Vector2 DirectionInput,
	BasicCharacter* TargetInput
)
{
	Position = PositionInput;
	Direction = DirectionInput;
	Target = TargetInput;

	if (!spawned) {
		// Sound effect
		Sound bulletImpactSound = LoadSound("resources/gunShoot.wav");
		PlaySound(bulletImpactSound);

		// Dont sound twice
		spawned = true;
	}


}


void Bullet::Draw()
{
	DrawRectangle(
		(int)Position.x,
		(int)Position.y,
		(int)Size.x,
		(int)Size.y,
		RED);
}


void Bullet::Impact()
{
	if (!impacted) {

		// For not impacting twice
		impacted = true;

		// Sound effect
		Sound bulletImpactSound = LoadSound("resources/gunImpact.wav");
		PlaySound(bulletImpactSound);

		WaitTime(1);

	}
}

void Bullet::Move()
{
	bool bIsInHorizontalRange = false;
	bool bIsInVeticalRange = false;

	if (
		Target->Position.x >= (Position.x + 20) ||
		Target->Position.x <= (Position.x - 20)
		) {
		bIsInHorizontalRange = true;
	}
	if (
		Target->Position.y >= (Position.y + 20) ||
		Target->Position.y <= (Position.y - 20)
		) {
		bIsInVeticalRange = true;
	}

	if (bIsInHorizontalRange && bIsInVeticalRange) {
		Impact();
	}
}
