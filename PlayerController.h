#pragma once
#include "Controller.h"
#include "BasicCharacter.h"
#include "Vehicle.h"

class PlayerController
{
public:
	PlayerController();

	int SCREEN_WIDTH = 1080;
	int SCREEN_HEIGHT = 720;
	int SCREEN_MARGIN_TOP_LEFT = 50;
	int SCREEN_MARGIN_BOTTOM_RIGHT = 50;

	BasicCharacter* character;
	BasicCharacter* getCharacter();
	Vehicle* VehicleTarget = new Vehicle();

	void Spawn();
	void SetTarget(Vehicle* VehicleInput);

	virtual void ListenAccelerateInput();
	virtual void ListenMovementInputs();
	virtual void ListenShootInput(HealthComponent* HealthComp);

	void ApplyDamage();
};