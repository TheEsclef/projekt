#include <raylib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "player.h"
#include "player.c"
#include "missiles.h"
#include "missiles.c"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 750

// Creating game objects
Rectangle ground = {0, 640, 750, 200};
Rectangle leftWall = {0, 0, 50, 800};
Rectangle rightWall = {700, 0, 50, 800};

// Custom colors for ingame use
Color green = {20, 160, 133, 255};

// Random values
char scoreText[20];
bool isGameOver = false;
int timer;
int score;
float spawnTimer;

// Function for restarting the game
void restartGame(void)
{
    score = 0; // To track the player's score
    timer = 0; // To track the time
    spawnTimer = 0.0f; // Spawn timer
    isGameOver = false; // Game state, if the game is over or not

    // Reset player position
    player.x = 350;
    player.y = 600;

    // Remove all missiles
    for (int i = 0; i < MAX_RECTS; i++)
    {
        rects[i].active = false;
    }
}

// Function for initialization
void init(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Aken"); // creates a window
    SetTargetFPS(60);                                // Sets the max FPS to 60
}

// Function for updating logic
void update(void)
{
    updatePlayer(); // Handles player movement

    // Simple counter to add score once every second
    timer++;
    if (timer >= 60)
    {
        score++;
        timer = 0; // reset the timer to 0
    }

    // Check for collisions with the left wall
    if (player.x < leftWall.x + leftWall.width)
    {
        player.x = leftWall.x + leftWall.width; // if player is colliding, pushes them back to simulate wall
    }
    // Check for collisions with the right wall
    if (player.x + player.width > rightWall.x)
    {
        player.x = rightWall.x - player.width; // if player is colliding, pushes them back to simulate wall
    }

    float dt = GetFrameTime(); // Gets the time from last frame
    spawnTimer += dt;          // adds it to the timer
    if (spawnTimer >= 1.0f)    // if more than a second has passed
    {
        for (int i = 0; i < (score / 5) + 1; i++) // every 20 score points it spawns 1 additional missile
        {
            spawnMissile(); // spawn the missile
        }
        spawnTimer = 0.0f; // reset the timer
    }
    updateMissiles(dt); // update the missile position

    // If any missile is colliding with the player
    if (checkMissileCollision(player))
    {
        isGameOver = true;
    }
}

// Function for drawing (in C you need to tell the program "alright now we're putting stuff on screen get ready")
void draw(void)
{
    BeginDrawing(); // starts the drawing process (utilizes the GPU)

    ClearBackground(green); // Clears away the previous frame, otherwise you'd get texture fighting

    drawMissiles();                     // Draw the missiles that fall
    DrawRectangleRec(player, WHITE);    // draws the player
    DrawRectangleRec(ground, GRAY);     // draws the ground
    DrawRectangleRec(leftWall, BLACK);  // draws the left wall
    DrawRectangleRec(rightWall, BLACK); // draws the rightwall
    DrawRectangle(0, 0, 750, 150, LIGHTGRAY);

    sprintf(scoreText, "Score: %d", score);
    DrawText(scoreText, 160, 15, 100, DARKBROWN);
    DrawText("A/D - Left/Right", 60, 650, 15, WHITE);
    DrawText("Space - Jump", 220, 650, 15, WHITE);
    DrawText("Esc - Exit the game", 550, 650, 15, WHITE);
    DrawText("Don't get hit, survive as long as you can", 60, 700, 30, WHITE);

    if (isGameOver == true)
    {
        DrawText("GAME OVER", 130, 300, 80, DARKPURPLE);
        DrawText("Press ENTER to RESTART", 100, 500, 40, DARKPURPLE);
    }

    EndDrawing(); // we tell the program "alright your bob ross era has ended"
}

// main function where we actually call everything
int main(void)
{
    init(); // initialize the scene

    // While the window should stay open
    while (!WindowShouldClose())
    {
        if (!isGameOver) // if the game isn't over
        {
            update(); // Call the update function
        }
        else
        {
            if (IsKeyPressed(KEY_ENTER)) // If the user presses ENTER
            {
                restartGame(); // Call the restart game function
            }
        }
        if (IsKeyPressed(KEY_ESCAPE)){ // Check if Esc was pressed
            CloseWindow(); // Close the window
        }
        draw(); // draw things onto tha screen
    }
    return 0;      // this nigga aint doin shit
}