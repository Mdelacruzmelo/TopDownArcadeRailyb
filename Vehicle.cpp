#include "Vehicle.h"
#include "Bullet.h"
#include "raymath.h"

Vehicle::Vehicle()
{
	Type = VEHICLE_STANDARD;
	static int Health = 0;
	Target = new BasicCharacter();

	Health = 100;
	AttackDamage = 20;
	Speed = 4;
	Size = { 40, 60 };
	Velocity = 5;
	bulletRate = 80;

	HealthComp.SetHealth(Health);
	HealthComp.SetMaxHealth(Health);
};

Vehicle::Vehicle(E_VehicleType TypeInput)
{
	Type = TypeInput;
	static int Health = 0;
	Target = new BasicCharacter();

	switch (Type)
	{
	case VEHICLE_HEAVY:
		Health = 400;
		AttackDamage = 40;
		Speed = 2;
		Size = { 60, 80 };
		Velocity = 2;
		bulletRate = 120;
		break;

	case VEHICLE_LIGHT:
		Health = 50;
		AttackDamage = 10;
		Speed = 8;
		Size = { 30, 40 };
		Velocity = 8;
		bulletRate = 40;
		break;

	case VEHICLE_STANDARD:
	default:
		Health = 100;
		AttackDamage = 20;
		Speed = 4;
		Size = { 40, 60 };
		Velocity = 5;
		bulletRate = 100;
		break;
	}

	HealthComp.SetHealth(Health);
	HealthComp.SetMaxHealth(Health);

}

HealthComponent* Vehicle::GetHealthComp()
{
	return &HealthComp;
}

Vector2 Vehicle::GetPosition()
{
	return Position;
}

void Vehicle::Draw()
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
			Fade(WHITE, opacity)
		);

		DrawHealthBar();
	}
}

void Vehicle::Explosion() {
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
				Fade(RED, explosionOpacity)
			);

			for (int i = 0; i < GetRandomValue(1, 5); i++) {
				DrawCircle(
					(int)Position.x + GetRandomValue(-20, 50),
					(int)Position.y + GetRandomValue(-20, 50),
					explosionRadius - GetRandomValue(60, 75),
					Fade(ORANGE, (explosionOpacity))
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

void Vehicle::Shoot()
{
	if (!beingDestroyed) {

		CheckShootFaster();

		Vector2 OriginBullet = Vector2{ Position.x, (Position.y + Size.y) };
		static Vector2 DirectionBullet = Vector2{ 0.f, 1.f };

		startBulletRate += 5;

		if (startBulletRate >= bulletRate) {
			startBulletRate = 0;
			shots++;
		}

		Bullet(
			OriginBullet,
			DirectionBullet,
			Target,
			ammunition,
			shots,
			bulletVelocity,
			AttackDamage
		);

	}
}

void Vehicle::CheckShootFaster() {

	if (Target != nullptr) {
		float distance = Target->Position.y - Position.y;
		if (distance >= 300) {
			bulletRate = 200;
		}
		else {
			bulletRate = 100;
		}
	}
}

void Vehicle::CheckDestroy() {
	if (!IsAlive()) {
		Destroy();
		Explosion();
	}
}

void Vehicle::Move()
{
	if (!beingDestroyed) {
		if (bIsGoingRight) {
			Position.x += Velocity * 1;
			if (Position.x >= TargetLocation.x) SetNextTargetLocation();
		}
		else {
			Position.x -= Velocity * 1;
			if (Position.x <= TargetLocation.x) SetNextTargetLocation();
		}
	}
}

void Vehicle::SetNextTargetLocation()
{
	if (bIsGoingRight) {
		bIsGoingRight = false;
		TargetLocation.x = GetRandomValue(100, 400);
	}
	else {
		bIsGoingRight = true;
		TargetLocation.x = GetRandomValue(500, 800);
	}
}

void Vehicle::SetTarget(BasicCharacter* TargetInput)
{
	Target = TargetInput;
}

bool Vehicle::IsAlive() {
	return HealthComp.GetHealth() > 0;
}

void Vehicle::Destroy()
{
	beingDestroyed = true;

	static int destroyedTime = 0;
	destroyedTime += 1;

	if (destroyedTime >= 100) {
		destroyed = true;
	}
}

void Vehicle::DrawHealthBar()
{
	static int BarWith = 100;
	static int BarHeight = 10;
	Vector2 BarPosition = Vector2{
		(Position.x - (BarWith / 2) + (Size.x / 2)),
		(Position.y - 20)
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
		Fade(RED, opacity));
}
