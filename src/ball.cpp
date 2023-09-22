#include "ball.h"
#include "game.h"
#include "raylib.h"


const int screenWidth = 800;
const int screenHeight = 600;
const float ballSize = 15;




void initBall(Ball& ball)
{  

    Vector2 ballPosition = { screenWidth / 2, screenHeight / 2 };

    ball.pos = ballPosition;

    ball.speed.x = 30;

}
void drawBall(Ball& ball)
{

    DrawRectangle(ball.pos.x, ball.pos.y, ballSize, ballSize, WHITE);

}



void updateBall(Ball& ball)
{

    ball.pos.x += ball.speed.x * GetFrameTime();
    ball.pos.y += ball.speed.y * GetFrameTime();


    if (ball.pos.y - ballSize <= 0 || ball.pos.y + ballSize >= screenHeight) {
        ball.speed.y *= -1;
    }
       


}

