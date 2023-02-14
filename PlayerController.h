#pragma once
#include "Controller.h"
#include "BasicCharacter.h"

class PlayerController : public Controller
{
public:
	PlayerController();

	int SCREEN_WIDTH = 1080;
	int SCREEN_HEIGHT = 720;
	int SCREEN_MARGIN_TOP_LEFT = 50;
	int SCREEN_MARGIN_BOTTOM_RIGHT = 50;

	BasicCharacter* character;
	void Spawn();
	virtual void ListenAccelerateInput();
	virtual void ListenMovementInputs();
	virtual void ListenShootInput();
	
	BasicCharacter* getCharacter();
};