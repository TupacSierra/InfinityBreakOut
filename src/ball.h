
#include "raylib.h"

struct Ball
{

    Vector2 pos;
    Vector2 speed;

};

void initBall(Ball& ball);
void drawBall(Ball& ball);
void updateBall(Ball& ball);
