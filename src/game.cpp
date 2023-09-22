#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 600;
const int paddleWidth = 115;
const int paddleHeight = 15;
const int brickWidth = 80;
const int brickHeight = 20;
const int brickRows = 5;
const int brickCols = 10;
const int ballRadius = 11;

Color bricksColors[brickRows] = { YELLOW, ORANGE, RED, PURPLE, GREEN };




//ARREGLOS :
// 
// Hacer que cuando terminen los bloques reseteen y aumente 1 la velocidad de la pelota 
// agregar una condicion de vida que sea igual a la cantidad de bloques y cuando reeseteen las vidas
// 
// Hacer que sea al mayor highscore 
// 
// Agregar menu y reemplazar todo a sigil y separar el codigo en .h y cpps
// 
// 
// Para cambiar el texto del score a sigil agregar #include <string>
// y hacer lo siguiente int score = 0;
// sting textoScore =  to_string(num);
// slText("Score: %d", textoScore.c_str(), 10, 10, 20, BLACK);




struct Ball { 
    Vector2 position;
    Vector2 speed;
    int radius;
} ball;

struct Paddle {
    Rectangle rect;
    float speed;
} paddle;



Rectangle bricks[brickRows][brickCols];


int score = 0;
bool gameover = false;



void InitGame() {
    // Initialize ball
    ball.position = { screenWidth / 2.0f, screenHeight / 2.0f };
    ball.speed = { 5.0f, 5.0f };
    ball.radius = ballRadius;

    // Initialize paddle
    paddle.rect = { screenWidth / 2 - paddleWidth / 2, screenHeight - 30, paddleWidth, paddleHeight };
    paddle.speed = 10;

    // Initialize bricks
    for (int i = 0; i < brickRows; i++) {
        for (int j = 0; j < brickCols; j++) {
            bricks[i][j] = { j * (float)(brickWidth + 10.0f), i * (float)(brickHeight + 10.0f), (float)brickWidth, (float)brickHeight };
        }
    }
}


void UpdateGame() {
    if (!gameover) {
        // Move the paddle
        if (IsKeyDown(KEY_LEFT)) {
            paddle.rect.x -= paddle.speed;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            paddle.rect.x += paddle.speed;
        }

        // Ball movement
        ball.position.x += ball.speed.x;
        ball.position.y += ball.speed.y;

        // Ball collisions with walls
        if (ball.position.x >= screenWidth - ball.radius || ball.position.x <= ball.radius) {
            ball.speed.x = -ball.speed.x;
        }
        if (ball.position.y <= ball.radius) {
            ball.speed.y = -ball.speed.y;
        }

        // Ball collision with paddle
        if (ball.position.y + ball.radius >= paddle.rect.y &&
            ball.position.y - ball.radius <= paddle.rect.y + paddle.rect.height &&
            ball.position.x >= paddle.rect.x &&
            ball.position.x <= paddle.rect.x + paddle.rect.width) {
            ball.speed.y = -ball.speed.y;


            float paddleCenterX = paddle.rect.x + paddle.rect.width / 2.0f;
            float offsetFromCenter = (ball.position.x - paddleCenterX) / (paddle.rect.width / 2.0f);
            ball.speed.x = 5.0f * offsetFromCenter;
        }


        // Ball collision with bricks
        for (int i = 0; i < brickRows; i++) {
            for (int j = 0; j < brickCols; j++) {
                if (bricks[i][j].width > 0 &&
                    ball.position.x + ball.radius >= bricks[i][j].x &&
                    ball.position.x - ball.radius <= bricks[i][j].x + bricks[i][j].width &&
                    ball.position.y + ball.radius >= bricks[i][j].y &&
                    ball.position.y - ball.radius <= bricks[i][j].y + bricks[i][j].height) {
                    bricks[i][j].width = 0;
                    ball.speed.y = -ball.speed.y;
                    score += 10;
                   
                        ball.speed.y++;
                        ball.speed.x++;
                    
                }
            }
        }

        // Check for game over
        if (ball.position.y >= screenHeight) {
            gameover = true;
        }
    }
}

void DrawGame() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!gameover) {
        // Draw ball
        DrawCircleV(ball.position, ball.radius, BLACK);

        // Draw paddle
        DrawRectangleRec(paddle.rect, BLUE);

        // Draw bricks
        for (int i = 0; i < brickRows; i++) {
            for (int j = 0; j < brickCols; j++) {
                if (bricks[i][j].width > 0) {
                    DrawRectangleRec(bricks[i][j], bricksColors[i]);
                }
            }
        }

        // Draw score
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
    }
    else {
        // Game over message
        DrawText("Game Over!", screenWidth / 2 - 80, screenHeight / 2, 30, RED);
        DrawText("Press R to Restart", screenWidth / 2 - 120, screenHeight / 2 + 40, 20, DARKGRAY);
    }

    EndDrawing();
}

int main() {
    InitWindow(screenWidth, screenHeight, "Breakout Game");
    SetTargetFPS(60);

    InitGame();

    while (!WindowShouldClose()) {
        UpdateGame();
        DrawGame();

        if (gameover && IsKeyPressed(KEY_R)) {
            InitGame();
            gameover = false;
            score = 0;
        }
    }

    CloseWindow();
    return 0;
}

