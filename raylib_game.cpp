/*******************************************************************************************
*
*   raylib game template
*
*   TopDownArcade
*   Deberes como si no hubiera un manyana
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "./Game.h"

int main(void)
{
	Game CurrentGame = Game();
	CurrentGame.Start();
}
