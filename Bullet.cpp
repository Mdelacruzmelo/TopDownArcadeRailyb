#include "Bullet.h"
#include "raymath.h"

Bullet::Bullet() {
}

Bullet::Bullet(
	Vector2 OriginInput,
	Vector2 Direction,
	BasicCharacter* TargetInput,
	int quantity,
	int bulletShoots,
	int velocity,
	int damage
)
{
	if (quantity > 0 && bulletShoots <= quantity) {

		Target = TargetInput;
		static int bulletDamage = damage;
		static Vector2* Positions = new Vector2[quantity];
		static bool* impacted = new bool[quantity];
		static bool* shooted = new bool[quantity];
		static Sound shootSound = LoadSound("resources/gunShoot.wav");
		static Sound impactSound = LoadSound("resources/bulletImpact.wav");
		static bool setOnce = false;

		if (!setOnce) {

			SetSoundVolume(shootSound, 0.2);
			SetSoundVolume(impactSound, 0.5);
			setOnce = true;

		}

		for (int i = 0; i < bulletShoots; i++) {

			if (shooted[i] != true) {

				PlaySound(shootSound);
				Positions[i] = OriginInput;
				shooted[i] = true;

			}

			if (impacted[i] != true) {

				Vector2 VectorVelocity = Vector2{ (float)velocity ,(float)velocity };
				Vector2 VectorToSum = Vector2Multiply(Direction, VectorVelocity);
				Positions[i] = Vector2Add(Positions[i], VectorToSum);

				DrawRectangle(
					(int)Positions[i].x,
					(int)Positions[i].y,
					(int)Size.x,
					(int)Size.y,
					RED);

				if (Positions[i].y >= 800 || Positions[i].y < 0) {
					impacted[i] = true;
				}

				bool collision = CheckCollisionRecs(
					Rectangle{ Positions[i].x, Positions[i].y, Size.x, Size.y },
					Rectangle{ Target->Position.x, Target->Position.y, Target->Size.x, Target->Size.y }
				);

				if (collision) {
					if (impacted[i] != true) {
						PlaySound(impactSound);
						Target->HealthComp.ApplyDamage(bulletDamage);
						impacted[i] = true;
					}
				}
			}
		}
	}
}

Bullet::Bullet(
	Vector2 OriginInput,
	Vector2 Direction,
	int quantity,
	int bulletShoots,
	int velocity,
	Vector2 VehiclePosition,
	HealthComponent* HealthCompInput
)
{
	if (quantity > 0 && bulletShoots <= quantity) {

		static Vector2* Positions = new Vector2[quantity];
		static bool* impacted = new bool[quantity];
		static bool* shooted = new bool[quantity];
		static Sound shootSound = LoadSound("resources/gunLaserShoot.wav");
		static Sound impactSound = LoadSound("resources/bulletImpact.wav");
		static bool setOnce = false;

		for (int i = 0; i < bulletShoots; i++) {

			if (!setOnce) {
				SetSoundVolume(shootSound, 0.5);
				SetSoundVolume(impactSound, 0.5);
				setOnce = true;
			}

			if (shooted[i] != true) {
				PlaySound(shootSound);
				Positions[i] = OriginInput;
				shooted[i] = true;
			}

			if (impacted[i] != true) {

				Vector2 VectorVelocity = Vector2{ (float)velocity ,(float)velocity };
				Vector2 VectorToSum = Vector2Multiply(Direction, VectorVelocity);
				Positions[i] = Vector2Add(Positions[i], VectorToSum);

				DrawRectangle(
					(int)Positions[i].x,
					(int)Positions[i].y,
					(int)Size.x,
					(int)Size.y,
					BLUE);

				bool bIsInHorizontalRange = false;
				bool bIsInVeticalRange = false;

				bool collision = CheckCollisionRecs(
					Rectangle{ Positions[i].x, Positions[i].y, Size.x, Size.y },
					Rectangle{ VehiclePosition.x, VehiclePosition.y, 40,60 }
				);

				// Get out of the screen
				if (Positions[i].y >= 800 || Positions[i].y < 0) {
					impacted[i] = true;
				}

				if (collision) {
					if (impacted[i] != true) {
						PlaySound(impactSound);
						HealthCompInput->ApplyDamage(12310);
						impacted[i] = true;
					}
				}
			}
		}
	}
}
