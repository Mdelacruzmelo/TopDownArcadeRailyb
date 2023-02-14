#pragma once
#include "raylib.h"
#include "screens.h"
#include "BasicCharacter.h"

class Enemy : public BasicCharacter
{
public:

	Enemy();
	Enemy(Vector2 InitialPosition);

	BasicCharacter* Target;
	void Attack();

};