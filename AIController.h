#pragma once
#pragma once
#include "Controller.h"
#include "BasicCharacter.h"
#include "Vehicle.h"

class AIController : public Controller
{
public:
	AIController();

	int SCREEN_WIDTH = 1080;
	int SCREEN_HEIGHT = 720;
	int SCREEN_MARGIN_TOP_LEFT = 50;
	int SCREEN_MARGIN_BOTTOM_RIGHT = 50;

	void SpawnVehicle();

	Vehicle VehicleStandard = Vehicle(VEHICLE_STANDARD);
	Vehicle VehicleHeavy = Vehicle(VEHICLE_HEAVY);
	Vehicle VehicleLight = Vehicle(VEHICLE_LIGHT);

};