#include "AIController.h"

AIController::AIController() {
	int limitTop = SCREEN_MARGIN_TOP_LEFT;
	int limitRight = SCREEN_WIDTH - SCREEN_MARGIN_BOTTOM_RIGHT;
	int limitBottom = SCREEN_HEIGHT - SCREEN_MARGIN_BOTTOM_RIGHT;
	int limitLeft = SCREEN_MARGIN_TOP_LEFT;
}


void AIController::SpawnVehicle() {

	VehicleStandard.Draw();
	VehicleStandard.Move();

	// VehicleHeavy.Draw(Vector2{ 370, 200 });
	// VehicleHeavy.Draw(Vector2{ 500, 250 });
	// VehicleLight.Draw(Vector2{ 200, 100 });
}