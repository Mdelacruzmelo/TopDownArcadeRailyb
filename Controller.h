#pragma once
#include "raylib.h"
#include "screens.h"

class Controller
{

public:
    int SCREEN_WIDTH = 1080;
    int SCREEN_HEIGHT = 720;
    int SCREEN_MARGIN_TOP_LEFT = 50;
    int SCREEN_MARGIN_BOTTOM_RIGHT = 50;

    Controller();
    Controller(
        int screenWidth,
        int screenHeight,
        int marginTopLeft,
        int marginBottomRight);

    virtual void ListenMovementInputs();
    virtual void ListenAccelerateInput();
};