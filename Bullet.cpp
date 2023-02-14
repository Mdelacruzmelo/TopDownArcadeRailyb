#include "Bullet.h"
#include "raymath.h"

Bullet::Bullet(
	Vector2 PositionInput,
	Vector2 Direction,
	BasicCharacter* TargetInput,
	int quantity
)
{
	if (quantity > 0) {

		Target = TargetInput;
		static Vector2* Positions = new Vector2[quantity];
		static bool* impacted = new bool[quantity];
		static bool* shooted = new bool[quantity];
		static int bulletRate = 0;
		static int bulletShoots = 1;
		static Sound shootSound = LoadSound("resources/gunShoot.wav");
		static Sound impactSound = LoadSound("resources/gunImpact.wav");

		bulletRate += 1;
		if (bulletRate >= 80) {
			bulletRate = 0;
			bulletShoots++;
		}

		for (int i = 0; i < bulletShoots; i++) {

			if (shooted[i] != true) {
				PlaySound(shootSound);
				Positions[i] = PositionInput;
				shooted[i] = true;
			}

			if (impacted[i] != true) {

				Vector2 VectorVelocity = Vector2{ (float)BulletVelocity ,(float)BulletVelocity };
				Vector2 VectorToSum = Vector2Multiply(Direction, VectorVelocity);
				Positions[i] = Vector2Add(Positions[i], VectorToSum);

				DrawRectangle(
					(int)Positions[i].x,
					(int)Positions[i].y,
					(int)Size.x,
					(int)Size.y,
					RED);

				bool bIsInHorizontalRange = false;
				bool bIsInVeticalRange = false;

				if ((Positions[i].x + 20) >= Target->Position.x &&
					(Positions[i].x - 20) <= Target->Position.x) {
					bIsInHorizontalRange = true;
				}

				if ((Positions[i].y + 20) >= Target->Position.y &&
					(Positions[i].y - 20) <= Target->Position.y) {
					bIsInVeticalRange = true;
				}

				if (Positions[i].y >= 800) {
					impacted[i] = true;
				}

				if (bIsInHorizontalRange && bIsInVeticalRange) {
					if (impacted[i] != true) {
						PlaySound(impactSound);
						impacted[i] = true;
					}
				}
			}
		}
	}
}