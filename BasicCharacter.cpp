#include "BasicCharacter.h"
#include "Bullet.h"
#include "Vehicle.h"
#include "raymath.h"

void BasicCharacter::Move(Vector2 inputValues)
{
	if (!beingDestroyed) {

		int MoveValue = (int)Velocity * (int)Acceleration;

		if (IsLimitedTop() && inputValues.y == -1)
		{
			inputValues.y = 0;
		}
		if (IsLimitedBottom() && inputValues.y == 1)
		{
			inputValues.y = 0;
		}
		if (IsLimitedRight() && inputValues.x == 1)
		{
			inputValues.x = 0;
		}
		if (IsLimitedLeft() && inputValues.x == -1)
		{
			inputValues.x = 0;
		}

		Vector2 MoveVector = Vector2{ (float)MoveValue, (float)MoveValue };
		Vector2 PositionInput = Vector2Multiply(MoveVector, inputValues);
		Position = Vector2Add(Position, PositionInput);

		DrawText(
			TextFormat(
				"Coord X: %d \nCoord Y: %d",
				(int)Position.x,
				(int)Position.y
			),
			100,
			300,
			16,
			WHITE);

	}
}

void BasicCharacter::Accelerate(bool active)
{
	if (active)
	{
		Acceleration += Acceleration < MAX_ACCELERATION ? 0.1f : 0.0f;
	}
	else
	{
		ResetAcceleration();
	}
}

void BasicCharacter::ResetAcceleration()
{
	Acceleration = InitialAcceleration;
}

bool BasicCharacter::IsLimitedRight()
{
	return Position.x >= screenLimitRight;
}

bool BasicCharacter::IsLimitedLeft()
{
	return Position.x <= screenLimitLeft;
}

bool BasicCharacter::IsLimitedTop()
{
	return Position.y <= screenLimitTop;
}

bool BasicCharacter::IsLimitedBottom()
{
	return Position.y >= screenLimitBottom;
}

void BasicCharacter::Draw()
{
	if (!destroyed) {

		if (beingDestroyed) {
			opacity -= 0.05f;
		}
		DrawRectangle(
			(int)Position.x,
			(int)Position.y,
			(int)Size.x,
			(int)Size.y,
			Fade(WHITE, opacity));

		DrawHealthBar();
	}

}

void BasicCharacter::SetSize(Vector2 size)
{
	Size = size;
}

void BasicCharacter::Shoot(Vector2 VehiclePosition, HealthComponent* HealthCompInput)
{
	if (!beingDestroyed) {
		Vector2 OriginBullet = Vector2{ Position.x, (Position.y + Size.y) };
		Vector2 DirectionBullet = Vector2{ 0.f, -1.f };

		Bullet(
			OriginBullet,
			DirectionBullet,
			ammunition,
			shots,
			bulletVelocity,
			VehiclePosition,
			HealthCompInput
		);
	}
}

bool BasicCharacter::IsAlive() {
	return HealthComp.GetHealth() > 0;
}

void BasicCharacter::DrawHealthBar()
{
	static int BarWith = 60;
	static int BarHeight = 10;
	Vector2 BarPosition = Vector2{
		(Position.x - (BarWith / 2) + (Size.x / 2)),
		(Position.y + Size.y + 10)
	};

	DrawRectangle(
		(int)BarPosition.x,
		(int)BarPosition.y,
		BarWith,
		BarHeight,
		Fade(GRAY, opacity));

	int HealthWidth = (int)(HealthComp.GetHealth() * BarWith / HealthComp.GetMaxHealth());

	DrawRectangle(
		(int)BarPosition.x,
		(int)BarPosition.y,
		HealthWidth,
		BarHeight,
		Fade(GREEN, opacity));
}


void BasicCharacter::Destroy()
{
	beingDestroyed = true;

	static int destroyedTime = 0;
	destroyedTime += 1;

	if (destroyedTime >= 100) {
		destroyed = true;
	}
}

void BasicCharacter::CheckDestroy() {
	if (!IsAlive()) {
		Destroy();
		Explosion();
	}
}

void BasicCharacter::Explosion() {

	static bool setOnce = false;
	static Sound explosionSound = LoadSound("resources/BombExplosion.wav");
	static float explosionRadius = GetRandomValue(80, 100);
	static float explosionOpacity = 1;
	static int particlesCount = 100;
	static Vector2* particles = new Vector2[particlesCount];
	static Vector2* particleDirections = new Vector2[particlesCount];

	if (!destroyed) {

		if (beingDestroyed) {

			if (!setOnce) {
				setOnce = true;
				PlaySound(explosionSound);

				for (int i = 0; i < particlesCount; i++) {
					particles[i] = Position;
					float randomX = GetRandomValue(-100, 100) / 10;
					float randomY = GetRandomValue(-100, 100) / 10;
					particleDirections[i] = Vector2{ randomX, randomY };
				}

			}

			explosionRadius += 0.2f;
			explosionOpacity -= 0.01f;

			DrawCircle(
				(int)Position.x,
				(int)Position.y,
				explosionRadius,
				Fade(BLUE, explosionOpacity)
			);

			for (int i = 0; i < GetRandomValue(1, 5); i++) {
				DrawCircle(
					(int)Position.x + GetRandomValue(-20, 50),
					(int)Position.y + GetRandomValue(-20, 50),
					explosionRadius - GetRandomValue(60, 75),
					Fade(GREEN, (explosionOpacity))
				);
			}

			for (int i = 0; i < particlesCount; i++) {
				static int particleRadius = 2;
				DrawCircle(
					(int)particles[i].x + GetRandomValue(-5, 5),
					(int)particles[i].y + GetRandomValue(-5, 5),
					particleRadius + GetRandomValue(1, 10),
					Fade(WHITE, (explosionOpacity))
				);
				particles[i] = Vector2Add(particles[i], particleDirections[i]);
			}
		}
	}
}