#include <raylib.h>

Rectangle collisionRec;

// Handles collision between two rectangles
void handleCollision(Rectangle x, Rectangle y)
{
    if (CheckCollisionRecs(x, y))
    {
        collisionRec = GetCollisionRec(x, y);

        if (collisionRec.width > collisionRec.height) // VERTICAL COLLISION
        {
            if (x.y < y.y) // If player hits the box from below
            {
                x.y -= collisionRec.height;
            }
            else // If player hits the box from above
            {
                x.y += collisionRec.height;
            }
        }
        else // HORIZONTAL COLLISION
        {
            if (x.x < y.x) // If player hits box from left
            {
                x.x -= y.x;
            }
            else // If player hits box from right
            {
                x.x += y.x;
            }
        }
    }
}

float handleVelocity(float velocity, float maxVelocity)
{
    if (velocity > maxVelocity)
    {
        velocity = maxVelocity;
    }
    else
    {
        velocity *= 1.04;
    }
    return velocity;
}