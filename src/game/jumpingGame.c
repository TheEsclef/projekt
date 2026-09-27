#include <raylib.h>
#include <stdio.h>
#include "physics.h"

#define SCREEN_WIDTH 750
#define SCREEN_HEIGHT 750
#define WALK_SPEED 4.0f
#define RUN_SPEED 6.0f

// DRAWN OBJECTS
Rectangle player = {400, 600, 20, 40};   // Creates the player object
Rectangle ground = {0, 640, 800, 200};   // Creates the ground object
Rectangle leftWall = {0, 0, 50, 800};    // Creates the wall to the left
Rectangle rightWall = {700, 0, 50, 800}; // Creates the wall to the right

// CUSTOM COLORS
Color green = {20, 160, 133, 255}; // defines the color green

// HANDLES PLAYER MOVEMENT
float velocity = 1.0f;
float jumpVelocity = 16.0f;
bool isJumping;
int jumpTimer;

// 1. Initialize the scene
void init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Aken"); // Creates the window
    SetTargetFPS(60);                                // Sets the FPS to 60
}

// 2. Handle Updates
void update()
{
    // Handle the player's max velocity to simulate running
    float currentMaxVelocity =
        IsKeyDown(KEY_LEFT_SHIFT)
            ? RUN_SPEED   // If player is holding shift down
            : WALK_SPEED; // If player isnt holding shift down

    if (IsKeyDown(KEY_D)) // if player moves Left
    {
        player.x += velocity;
        velocity = handleVelocity(velocity, currentMaxVelocity); // Increases velocity as player moves
    }
    else if (IsKeyDown(KEY_A)) // if player moves Right
    {
        player.x -= velocity;
        velocity = handleVelocity(velocity, currentMaxVelocity); // Increases velocity as player moves
    }
    else
    {
        velocity = 1; // after moving stops, sets the velocity back to default
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        isJumping = true; // when space is pressed, toggled jumping
    }

    if (isJumping) // handles Jumping
    {
        jumpTimer += 1; // tick up a timer

        if (jumpTimer < 40) // for 40 frames player moves up
        {
            player.y -= jumpVelocity;
            jumpVelocity *= 0.92; // gradually decrease the speed at which player rises
        }
        else // for 40 frames player moves down
        {
            player.y += jumpVelocity;
            jumpVelocity *= 1.08; // gradually increase the speed at which player falls
        }
        if (jumpTimer >= 81) // After jump cycle has ended
        {
            jumpTimer = 0;        // reset the jumptimer
            jumpVelocity = 16.0f; // reset the velocity
            player.y = 600;       // Reset the player position after jump (makes it seem as if everything works wonderfully)
            isJumping = false;
        }
    }
    if (player.x < leftWall.x + leftWall.width)
    {
        player.x = leftWall.x + leftWall.width;
    }
    if (player.x + player.width > rightWall.x)
    {
        player.x = rightWall.x - player.width;
    }
}

// 3. Handle drawing
void draw()
{
    BeginDrawing();

    ClearBackground(green);

    DrawRectangleRec(player, WHITE);
    DrawRectangleRec(ground, GRAY);
    DrawRectangleRec(rightWall, BLACK);
    DrawRectangleRec(leftWall, BLACK);
    EndDrawing();
}

int main()
{
    init();

    while (!WindowShouldClose())
    {
        update();
        draw();
    }

    CloseWindow();
    return 0;
}