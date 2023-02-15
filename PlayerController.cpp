#include "Controller.h"
#include "PlayerController.h"

PlayerController::PlayerController() {

	VehicleTarget = new Vehicle();
	character = new BasicCharacter();
}

void PlayerController::ListenAccelerateInput()
{
	bool buttonPressed = IsKeyDown(KEY_LEFT_SHIFT);
	character->Accelerate(buttonPressed);
}

BasicCharacter* PlayerController::getCharacter()
{
	return character;
}

void PlayerController::ListenMovementInputs()
{
	static Vector2 inputValues = { 0, 0 };
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S))
	{
		if (IsKeyDown(KEY_W)) inputValues.y = -1;
		if (IsKeyDown(KEY_S)) inputValues.y = 1;
	}
	else {
		inputValues.y = 0;
	}

	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
	{
		if (IsKeyDown(KEY_A)) inputValues.x = -1;
		if (IsKeyDown(KEY_D)) inputValues.x = 1;
	}
	else {
		inputValues.x = 0;
	}

	character->Move(inputValues);
}

void PlayerController::ListenShootInput(HealthComponent* HealthCompInput)
{
	static bool startedShoot = false;
	static int bulletRate = 0;

	bulletRate += 1;

	if (bulletRate >= character->bulletRate) {
		bulletRate = 0;
		startedShoot = false;
	}

	if (IsKeyDown(KEY_SPACE))
	{
		if (!startedShoot) {
			startedShoot = true;
			bulletRate = 1;
			character->shots += 1;
			character->ammunition -= 1;
		}
		else if (bulletRate == 0) {
			character->shots += 1;
			character->ammunition -= 1;
		}
	}

	character->Shoot(VehicleTarget->Position, HealthCompInput);

}

void PlayerController::ApplyDamage()
{
	VehicleTarget->HealthComp.ApplyDamage(100);
}

void PlayerController::Spawn()
{
	character->Draw();
	character->CheckDestroy();
}

void PlayerController::SetTarget(Vehicle* VehicleInput) {
	VehicleTarget = VehicleInput;
}
