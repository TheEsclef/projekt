#include <raylib.h>
#include <stdbool.h>

#include "player.h"
#include "physics.h"

#define WALK_SPEED 4.0f
#define RUN_SPEED 6.0f

// Create the player object
Rectangle player = {400, 600, 60, 40};

static float velocity = 1.0f; // Set a velocity for horizontal movement
static float jumpVelocity = 16.0f; // Sets the jump velocity for the player
static bool isJumping = false; // Create state for whether or not player is jumping
static int jumpTimer = 0; // Create a timer to check how long user has been jumping for

void updatePlayer(void)
{
    // Sets the current max velocity to either walk speed or run speed depending on if shift is pressed
    float currentMaxVelocity =
        IsKeyDown(KEY_LEFT_SHIFT)
            ? RUN_SPEED
            : WALK_SPEED;

    if (IsKeyDown(KEY_D)) // move character to left
    {
        player.x += velocity;
        velocity = handleVelocity(velocity, currentMaxVelocity);
    }
    else if (IsKeyDown(KEY_A)) // move character to right
    {
        player.x -= velocity;
        velocity = handleVelocity(velocity, currentMaxVelocity);
    }
    else // set the velocity back to 1 and do nothing ( like sten )
    {
        velocity = 1.0f;
    }

    if (IsKeyPressed(KEY_SPACE)) // turns the isJumping bool into true and begins jumping sequence
    {
        isJumping = true;
    }

    if (isJumping) // Jumping sequence
    {
        jumpTimer++; // add 1 to jumpTimer every second

        if (jumpTimer < 40) // Lift the player gradually slowing the velocity to simulate gravity
        {
            player.y -= jumpVelocity;
            jumpVelocity *= 0.92f;
        }
        else // same thing but this time increase the velocity to simulate gravity
        {
            player.y += jumpVelocity;
            jumpVelocity *= 1.08f;
        }

        if (jumpTimer >= 81) // Jumping sequence has ended and reset values
        {
            jumpTimer = 0;
            jumpVelocity = 16.0f;
            player.y = 600;
            isJumping = false;
        }
    }
}