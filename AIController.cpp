#pragma once
#include "AIController.h"

AIController::AIController(BasicCharacter* TargetInput) {
	int limitTop = SCREEN_MARGIN_TOP_LEFT;
	int limitRight = SCREEN_WIDTH - SCREEN_MARGIN_BOTTOM_RIGHT;
	int limitBottom = SCREEN_HEIGHT - SCREEN_MARGIN_BOTTOM_RIGHT;
	int limitLeft = SCREEN_MARGIN_TOP_LEFT;
	Target = TargetInput;
}


void AIController::SpawnVehicleStandard() {
	VehicleStandard.Draw();
}

void AIController::Play() {
	VehicleStandard.SetTarget(Target);
	VehicleStandard.Move();
	VehicleStandard.CheckDestroy();
	VehicleStandard.Shoot();
}

Vehicle* AIController::getVehiclePawn()
{
	return &VehicleStandard;
}
