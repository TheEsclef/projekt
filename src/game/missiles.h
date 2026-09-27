#ifndef MISSILES_H
#define MISSILES_H

// THESE ARE DECLARATIONS, THESE ARE NEEDED SO THE OTHER FILES CAN FIND THESE FUNCTIONS
void spawnMissile(void);
void drawMissiles(void);
void updateMissiles(float deltaTime);
bool checkMissileCollision(Rectangle player);

#endif