#include <raylib.h>
#define MAX_RECTS 30

// We create a missile type
typedef struct
{
    Rectangle rect;
    Color color;
    float speed;
    bool active;
} missile;
missile rects[MAX_RECTS];

// simple check to see if missile collided with player
bool checkMissileCollision(Rectangle player){
    for (int i = 0; i < MAX_RECTS; i++){ // For every missile
        if (rects[i].active){ // If the missile is active (not deleted)
            if (CheckCollisionRecs(rects[i].rect, player)){ // check if its colliding with the player
                return true; // if it is, return true
            }
        }
    }
    return false; // Returns false if nothing is found
}

// Creates a new missile at a random X position above the screen
void spawnMissile(void)
{
    // Find an unused missile slot
    for (int i = 0; i < MAX_RECTS; i++)
    {
        if (!rects[i].active)
        {
            // Enable this missile
            rects[i].active = true;

            // Set missile size
            rects[i].rect.width = 50;
            rects[i].rect.height = 30;

            // Spawn at a random X position, just above the screen
            rects[i].rect.x = GetRandomValue(0, GetScreenWidth() - 50);
            rects[i].rect.y = -30;

            // Set appearance and movement speed
            rects[i].color = RED;
            rects[i].speed = 200.0f;

            // Stop after spawning one missile
            break;
        }
    }
}

// Draw all active missiles
void drawMissiles(void)
{
    for (int i = 0; i < MAX_RECTS; i++) // for Every missile there is
    {
        if (rects[i].active) // If it is active
        {
            DrawRectangleRec(rects[i].rect, rects[i].color); // Draw it
        }
    }
}

// Move missiles and remove them when they leave the screen
void updateMissiles(float deltaTime)
{
    for (int i = 0; i < MAX_RECTS; i++) // For every missile there is
    {
        if (rects[i].active) // If it is active
        {
            // Move the missile downward
            rects[i].rect.y += rects[i].speed * deltaTime;

            // Disable the missile when it goes off-screen
            if (rects[i].rect.y > GetScreenHeight())
            {
                rects[i].active = false; // unactivate the missile
            }
        }
    }
}