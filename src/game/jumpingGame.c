#include <raylib.h>
#include <stdio.h>
#include "player.h"
#include "player.c"

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
int timer;
int score;

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
    if(timer >= 60){
        score++;
        timer = 0;
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
}

// Function for drawing (in C you need to tell the program "alright now we're putting stuff on screen get ready")
void draw(void)
{
    BeginDrawing(); // starts the drawing process (utilizes the GPU)

    ClearBackground(green); // Clears away the previous frame, otherwise you'd get texture fighting

    DrawRectangleRec(player, WHITE);    // draws the player
    DrawRectangleRec(ground, GRAY);     // draws the ground
    DrawRectangleRec(leftWall, BLACK);  // draws the left wall
    DrawRectangleRec(rightWall, BLACK); // draws the rightwall
    DrawRectangle(0, 0, 750, 150, LIGHTGRAY);

    sprintf(scoreText, "Score: %d", score);
    DrawText(scoreText, 160, 15, 100, DARKBROWN);
    DrawText("A/D - Left/Right", 100, 650, 15, WHITE);
    DrawText("Space - Jump", 320, 650, 15, WHITE);
    DrawText("Esc - Exits the game", 500, 650, 15, WHITE);
    DrawText("Don't get hit, survive as long as you can", 60, 700, 30, WHITE);

    EndDrawing(); // we tell the program "alright your bob ross era has ended"
}

// main function where we actually call everything
int main(void)
{
    init(); // initialize the scene

    while (!WindowShouldClose()) // if the window shouldnt close, then....
    {
        update(); // update game logic and values
        draw();   // draw things onto the screen
    }

    CloseWindow(); // we should close the windows right about now
    return 0;      // this nigga aint doin shit
}