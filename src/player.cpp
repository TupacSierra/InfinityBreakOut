#include"player.h"
#include "game.h"
#include "raylib.h"

const int paddleWidth = 15;
const int paddleHeight = 100;

void initPlayer(Player& player, Player& player2)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    

    player = { 20, screenHeight / 2 - paddleHeight / 2, 0 };
    player2 = { screenWidth - 30, screenHeight / 2 - paddleHeight / 2, 0 };

   
}
void drawPlayer(Player& player, Player& player2)
{
 

    DrawRectangle(player.posx, player.posy, paddleWidth, paddleHeight, WHITE);
    DrawRectangle(player2.posx, player2.posy, paddleWidth, paddleHeight, WHITE);
   

}

void updatePlayer(Player& player, Player& player2)
{

    if (IsKeyDown(KEY_W)) player.posy -= 128.0 * GetFrameTime();
    if (IsKeyDown(KEY_S))player.posy += 128.0 * GetFrameTime();

    if (IsKeyDown(KEY_UP))player2.posy -= 128.0 * GetFrameTime();
    if (IsKeyDown(KEY_DOWN))player2.posy += 128.0 * GetFrameTime();


}



